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

INTERNAL const unsigned SUCCESS = 1;
INTERNAL const unsigned FAILURE = 0;
INTERNAL const unsigned WINDOW_FAILURE_CODE = 1;
INTERNAL const unsigned RENDERER_FAILURE_CODE = 2;
INTERNAL const unsigned TEXTURE_FAILURE_CODE = 3;

INTERNAL void game_quit(const int game_exit_code)
{
	SDL_Quit();
	exit(game_exit_code);
}

INTERNAL void game__modify_texture(SDL_Texture* game_texture, SDL_Color* colour)
{
	int game_texture_width = 0;
	int game_texture_height = 0;
	SDL_QueryTexture(game_texture, NULL, NULL, &game_texture_width, &game_texture_height);

	void* game_texture_pixels = NULL;	
	int game_texture_pitch = 0;

	u32* game_texture_pixel = NULL;

	if (SDL_LockTexture(game_texture, NULL, &game_texture_pixels, &game_texture_pitch) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to lock game texture: %s\n", SDL_GetError());	
		game_quit(TEXTURE_FAILURE_CODE);
	}

	for (int game_texture_row = 0; game_texture_row < game_texture_width; ++game_texture_row) {
		game_texture_pixel = (u32 *)((u8 *)(game_texture_pixels) + game_texture_row * game_texture_pitch);
		for (int game_texture_col = 0; game_texture_col < game_texture_height; ++game_texture_col) {
			*game_texture_pixel++ = (0xFF000000 | (colour->r << 16) | (colour->g << 8) | (colour->b));
		}
	}	
	
	SDL_UnlockTexture(game_texture);	
}

INTERNAL void game__resize_texture(SDL_Texture* game_texture, SDL_Renderer* game_renderer, int current_game_width, int current_game_height)
{
	SDL_DestroyTexture(game_texture);	

	game_texture = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					current_game_width, current_game_height);

	if (game_texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to resize game texture: %s\n", SDL_GetError());	
		game_quit(TEXTURE_FAILURE_CODE);
	}
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

	SDL_Texture* game_texture = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
											game_width, game_height);

	if (game_texture == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create game texture: %s\n", SDL_GetError());	
		game_quit(TEXTURE_FAILURE_CODE);
	}

	bool game_is_running = true;

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
					game__resize_texture(game_texture, game_renderer, event.window.data1, event.window.data2);
				 } break;
				 case SDL_WINDOWEVENT_EXPOSED:
				 {
					SDL_RenderCopy(game_renderer, game_texture, NULL, NULL); 
					SDL_RenderPresent(game_renderer);
				 } break;
				}
			 } break;

			 case SDL_KEYDOWN:
			 {
				SDL_Keycode entered_keycode = event.key.keysym.sym;
				if (entered_keycode == SDLK_w) {
					puts("w");		
				}
			 } break;
			} // end-event-switch	
		} // end-event-while 
	} // end-game-while	

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

