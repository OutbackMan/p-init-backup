#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define PI32 3.14159265359f
#define LOCAL_PERSIST static
#define INTERNAL static
#define BLACK {0, 0, 0, 255}
#define GREY {128, 128, 128, 255}
#define WHITE {255, 255, 255, 255}
#define BROWN {165, 42, 42, 255}
#define RED {255, 0, 0, 255}
#define ORANGE {255, 165, 0, 255}
#define YELLOW {255, 255, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}
#define PURPLE {128, 0, 128, 255}
#define BG_COLOUR BLACK

INTERNAL inline u32 sdl_colour_to_bitmask(SDL_Colour* colour)
{
	return ((colour->a << 24) | (colour->r << 16) | 
				(colour->g << 8) | colour->b);	
}

typedef float real32;
typedef double real64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int STATUS_CODE;

enum {
	SENTINEL_CODE = -1,
	SUCCESS_CODE = 1,
    FAILURE_CODE = 0,
    WINDOW_FAILURE_CODE = 1,
    RENDERER_FAILURE_CODE = 2,
    TEXTURE_FAILURE_CODE = 3,
    SURFACE_FAILURE_CODE = 4,
};

INTERNAL STATUS_CODE game__set_surface_pixel_colour(SDL_Surface* game_surface, int x, int y, SDL_Color* colour)
{
	if (ASSERT_IF(game_surface != NULL && colour != NULL, "Null parameters")) {
		return INVALID_ARGUMENTS; 	
	}

	if (SDL_MUSTLOCK(game_surface)) {
		if (SDL_LockSurface(game_surface) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to lock game surface: %s\n", SDL_GetError());	
			return SURFACE_FAILURE_CODE;
		}
	}

	u8* surface_pixel = (u8 *)game_surface->pixels;
	surface_pixel += (y * game_surface->pitch) + (x * sizeof(u8));
	*surface_pixel = (colour->a | (colour->r << 16) | (colour->g << 8) | (colour->b));

	if (SDL_MUSTLOCK(game_surface)) {
		SDL_UnlockSurface(game_surface);		
	}

	return SUCCESS_CODE;
}

// consider offsetting so as to highlight border, e.g: (y + 2) * width + (x + 2)
#define UBORDER_COLLISION(row, col) \
	((col == 0) || (col == WINDOW_WIDTH - 1) || (row == WINDOW_HEIGHT - 1))

INTERNAL STATUS_CODE game__set_starting_surface(SDL_Surface* game_surface)
{
	SDL_Color bg_colour = BG_COLOUR;
	u32 bg_bitmask = (bg_colour.a | (bg_colour.r << 16) | (bg_color.g << 8) | bg_color.b)

	if (SDL_MUSTLOCK(game_surface)) {
		if (SDL_LockSurface(game_surface) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to lock game surface: %s\n", SDL_GetError());	
			return SURFACE_FAILURE_CODE;
		}
	}

	for (int game_surface_row = 0; game_surface_row < game_width; ++game_surface_row) {
		game_surface_pixel = (u32 *)((u8 *)(game_surface_pixels) + game_surface_row * game_surface_pitch);
		for (int game_surface_col = 0; game_surface_col < game_height; ++game_surface_col) {
			if (UBORDER_COLLISION(game_surface_row, game_surface_col)) {
				*game_surface_pixel++ = bg_bitmask;
			}
		}
	}	

	if (SDL_MUSTLOCK(game_surface)) {
		SDL_UnlockSurface(game_surface);		
	}

	return SUCCESS_CODE;
}

INTERNAL STATUS_CODE game__resize_texture(SDL_Texture* game_texture, SDL_Renderer* game_renderer, int current_game_width, int current_game_height)
{
	// Keep in production code unless a dramatic speed-up is noticed.
	// However, assert to a log file instead of stdout.
	assert(game_texture != NULL && game_renderer != NULL);

	SDL_DestroyTexture(game_texture);	

	game_texture = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					current_game_width, current_game_height);

	if (game_texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to resize game texture: %s\n", SDL_GetError());	
		return TEXTURE_FAILURE_CODE;
	}

	return SUCCESS_CODE;
}

INTERNAL STATUS_CODE game_start(const unsigned game_width, const unsigned game_height)
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

	int exit_code = SENTINEL_CODE;

	SDL_Window* game_window = NULL;
	SDL_Renderer* game_renderer = NULL;
	SDL_Surface* game_surface = NULL;
	SDL_Texture* game_texture = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialise game SDL backend: %s\n", SDL_GetError());	
		exit_code = FAILURE_CODE;
		goto __exit;
	}

	game_window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									game_width, game_height, SDL_WINDOW_RESIZABLE);
	
	if (game_window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game window: %s\n", SDL_GetError());	
		exit_code = WINDOW_FAILURE_CODE;
		goto __exit;
	}

	game_renderer = SDL_CreateRenderer(game_window, -1, 0);

	if (game_renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game renderer: %s\n", SDL_GetError());	
		exit_code = RENDERER_FAILURE_CODE;
		goto __exit;
	}

	game_surface = SDL_CreateRGBSurface(0, game_width, game_height, 32,
									0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	if (game_surface == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game surface: %s\n", SDL_GetError());	
		exit_code = SURFACE_FAILURE_CODE;
		goto __exit;
	}

	if (game__set_starting_surface(game_surface) == SURFACE_FAILURE_CODE) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to set starting game surface: %s\n", SDL_GetError());	
		exit_code = SURFACE_FAILURE_CODE;
		goto __exit;
	}

	game_texture = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
											game_width, game_height);

	if (game_texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game texture: %s\n", SDL_GetError());	
		exit_code = TEXTURE_FAILURE_CODE;
		goto __exit;
	}

	bool game_is_running = true;

	int current_piece = 0;
	int current_rotation = 0;
	int current_x = FIELD_WIDTH / 2;
	int current_y = 0;

	while (game_is_running) {
		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			 case SDL_QUIT:
			 {
				game_is_running = false;	 
			 } break;

			 case SDL_WINDOWEVENT:
			 {
				switch (event.window.event) {
				 case SDL_WINDOWEVENT_RESIZED:
				 {
					if (game__resize_texture(game_texture, game_renderer, event.window.data1, event.window.data2) != SUCCESS_CODE) {
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to resize game texture: %s\n", SDL_GetError());	
						exit_code = TEXTURE_FAILURE_CODE;
						goto __exit;
					}
				 } break;
				 case SDL_WINDOWEVENT_EXPOSED:
				 {
					if (SDL_UpdateTexture(game_texture, NULL, game_surface->pixels, game_surface->pitch) < 0) {
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to update game texture: %s\n", SDL_GetError());	
						exit_code = TEXTURE_FAILURE_CODE;
						goto __exit;
					}
					if (SDL_RenderClear(game_renderer) < 0) {
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to clear game renderer: %s\n", SDL_GetError());	
						exit_code = RENDERER_FAILURE_CODE;
						goto __exit;
					}
					if (SDL_RenderCopy(game_renderer, game_texture, NULL, NULL) < 0) {
						SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to copy to game renderer: %s\n", SDL_GetError());	
						exit_code = RENDERER_FAILURE_CODE;
						goto __exit;
					} 
					SDL_RenderPresent(game_renderer);
				 } break;
				}
			 } break;

			 case SDL_KEYDOWN:
			 {
				SDL_Keycode entered_keycode = event.key.keysym.sym;
				if (entered_keycode == SDLK_ESCAPE) {
					game_is_running = false;
				}
			 } break;
			} // end-event-switch	
		} // end-event-while 
	} // end-game-while	

	__exit:
		if (game_surface != NULL) SDL_FreeSurface(game_surface);
		if (game_texture != NULL) SDL_DestroyTexture(game_texture);
		if (game_renderer != NULL) SDL_DestroyRenderer(game_renderer);
		if (game_window != NULL) SDL_DestroyWindow(game_window);
		if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_Quit(); // can also pass SDL_INIT_EVERYTHING
		return exit_code;
}

// Assets
SDL_Color tetromino[7][16] = {0};

tetromino[0] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR
};

tetromino[1] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[2] = {
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[3] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[4] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[5] = {
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR
};

tetromino[6] = {
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR
};

int tetromino_rotate(int original_x_index, int original_y_index, int angle_index)
{
	switch (angle_index % 4) {
	 case 0:
	 {
		return original_y_index * 4 + original_x_index; // 0 degrees 
	 } break;
	 case 1:
	 {
		return 12 + original_y_index - (original_x_index * 4); // 90 degrees 
	 } break;
	 case 2:
	 {
		return 15 - (original_y_index * 4) - original_x_index; // 180 degrees 
	 } break;
	 case 3:
	 {
		return 3 - original_y_index + (original_x_index * 4); // 270 degrees 
	 } break;
	}

	return 0;
}

bool does_tetromino_fit(int tetromino_id, int current_rotation, int top_x, int top_y)
{
	// texture size
	// texture colour information, i.e. what colour its 'body' is
	// SDL_Colour comparison
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int index = tetromino_rotate(i, j, current_rotation);	
			int field_index = (top_y + j) * FIELD_WIDTH + (top_x + i);

			if (i + top_x >= 0 && i + top_x < FIELD_WIDTH) {
				if (j + top_y >= 0 && j + top_y < FIELD_HEIGHT) {
					if (tetromino[tetromino_id][index] == PIECE_COLOUR && field[index] != BG) {
						return false;
					}
				}		
			}
		}		
	}

	return true;	
}

// cross platform coverage (codecov), profiler (easy profiler)
// 1. ASSETS: items, map

/*
game {
	window, renderer, is_running,
	assets(map, tetromino) // can scale further if necessary
}
*/


// ISA from intel architecture reference
// cycles may be from other processes due to the CPU swapping
// may downclock or upclock itself
// only indicative of how much work CPU did
int main(int argc, char* argv[argc + 1])
{
	const unsigned GAME_WIDTH = 640;
	const unsigned GAME_HEIGHT = 480;

	Game game = {0};

	game_init(&game, title, width, height);

	game_start(&game);

	// how many counter increments per second
	uint64_t counter_frequency = SDL_GetPerformanceFrequency();
	uint64_t last_counter = SDL_GetPerformanceCounter();
	uint64_t end_counter = 0;
	
	while (game_is_running(&game)) {
		game_handle_events();
		
		game_update();
		
		end_counter = SDL_GetPerformanceQuery();

		uint64_t counter_elapsed = end_counter - last_counter;

		// multiplying by 1000 prevents result truncation to 0
		uint64_t ms_per_frame = (1000 * counter_elapsed) / counter_frequency;
		// dimensional analysis
		uint64_t fps = (counter_frequency / counter_elapsed);

		last_counter = end_counter;
	}

	game_exit();
}

