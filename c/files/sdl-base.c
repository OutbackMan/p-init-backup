#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define PI32 3.14159265359f
#define LOCAL_PERSIST static
#define INTERNAL static

typedef float real32;
typedef double real64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

INTERNAL const unsigned SUCCESS = 1
INTERNAL const unsigned FAILURE = 0
INTERNAL const unsigned WINDOW_FAILURE_CODE = 1
INTERNAL const unsigned RENDERER_FAILURE_CODE = 2
INTERNAL const unsigned TEXTURE_FAILURE_CODE = 3

INTERNAL void game_quit(const int game_exit_code)
{
	SDL_Quit();
	exit(game_exit_code);
}

INTERNAL void texture_set_colour(SDL_Texture* texture, SDL_Color* colour)
{
	int texture_width = 0;
	int texture_height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

	void* texture_pixels = NULL;	
	int texture_pitch = 0;

	uint32_t* texture_pixel = NULL;

	if (SDL_LockTexture(texture, NULL, &texture_pitch, &texture_width) < 0) {
		fprintf(stderr, "Error encountered: %s\n", SDL_GetError());	
		return;
	}

	for (int row = 0; row < texture_width; ++row) {
		texture_pixel = (uint32_t *)((uint8_t *)(texture_pixels) + row * texture_pitch)
		for (int col = 0; col < texture_height; ++col) {
			*texture_pixel++ = (0xFF000000 | (colour->r << 16) | (colour->g << 8) | (colour->b));
		}
	}	
	
	SDL_UnlockTexture(texture);	
}

INTERNAL void resize_sdl_texture(SDL_Texture* texture, SDL_Renderer* renderer, int width, int height)
{
	if (texture != NULL) {
		SDL_DestroyTexture(texture);	
	}	

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					width, height);
}

INTERNAL void game__draw_texture(SDL_Window* game_window, SDL_Texture* game_texture)
{
	int current_game_width = 0;
	int current_game_height = 0;

	SDL_GetWindowSize(game_window, &window_width, &window_height);

	SDL_Renderer* renderer = SDL_GetRenderer(window);

	void* texture_pixels = NULL;
	int texture_pitch = 0; // bytes per row
	if (SDL_LockTexture(window_texture, NULL, &texture_pitch, &texture_width) < 0) {
		fprintf(stderr, "Error encountered: %s\n", SDL_GetError());	
		return;
	}

	// Obtain desired colour from somewhere
	memset(texture_pixels, 0, texture_pitch * window_height);

	SDL_UnlockTexture(window_texture);

	SDL_RenderCopy(renderer, window_texture, NULL, NULL); 
	SDL_RenderPresent(renderer);
}


INTERNAL int game_start(const unsigned game_width, const unsigned game_height)
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialise game SDL backend: %s\n", SDL_GetError());	
		return FAILURE;
	}

	SDL_Window* game_window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									game_width, game_height, SDL_WINDOW_RESIZABLE);
	
	if (game_window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game window: %s\n", SDL_GetError());	
		game_quit(WINDOW_FAILURE_CODE);
	}

	SDL_Renderer* game_renderer = SDL_CreateRenderer(game_window, -1, 0);

	if (game_renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game renderer: %s\n", SDL_GetError());	
		game_quit(RENDERER_FAILURE_CODE);
	}

	SDL_Texture* game_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
											game_width, game_height);

	if (game_texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game texture: %s\n", SDL_GetError());	
		game_quit(TEXTURE_FAILURE_CODE);
	}

	bool game_is_running = true;

	while (game_is_running) {
		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			switch (event->type) {
			 case SDL_QUIT:
			 {
				game_is_running = false;	 
			 } break;

			 case SDL_WINDOWEVENT:
			 {
				switch (event->window.event) {
				 case SDL_WINDOWEVENT_RESIZED:
				 {
					game__resize_texture(game_texture, event->window.data1, event->window.data2);
				 } break;
				 case SDL_WINDOWEVENT_EXPOSED:
				 {
					game__draw_texture(game_texture);
				 } break;
				}
			 } break;

			 case SDL_KEYDOWN:
			 case SDL_KEYUP:
			 {
				SDL_Keycode entered_keycode = event->key.keysym.sym;
				 
			 }
		bool key_is_down = (event->key.state == SDL_PRESSED);
		bool key_was_down = false;
		if (event->key.state == SDL_RELEASED || event->key.repeat != 0) {
			key_was_down = true;		
		}

		if (event->key.repeat == 0) {
			if (keycode == SDLK_w) {
				printf("w %s\n", (key_is_down ? "is down" : "was down"));
			} else if (keycode == SDLK_a) {
				
			}
		}

		bool alt_key_was_down = (event->key.keysym.mod & KMOD_ALT);
		if (keycode == SDLK_F4 && alt_key_was_down) {
			// ...		
		}
	 }

	 default:
	 {
		break;
	 }
	}		
					
		}	
		// logic, draw
	}

	// cleanup

	return SUCCESS;
}

int main(int argc, char* argv[argc + 1])
{
	const unsigned GAME_WIDTH = 640;
	const unsigned GAME_HEIGHT = 480;

	if (game_start(GAME_WIDTH, GAME_HEIGHT) == FAILURE) {
		return EXIT_FAILURE;
	} else {
		return EXIT_SUCCESS;
	}
}

