#include "core/game.h"
typedef struct {
	// renderer, surface, window, etc.	
} Game;

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define PI32 3.14159265359f

INTERNAL inline u32 sdl_colour_to_bitmask(SDL_Colour* colour)
{
	return ((colour->a << 24) | (colour->r << 16) | 
				(colour->g << 8) | colour->b);	
}

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

INTERNAL STATUS_CODE game__resize_texture(Game* game, int current_game_width, int current_game_height)
{
	GAME_ASSERT(game != NULL, "msg");

	SDL_DestroyTexture(game_texture);	

	game->texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
					current_game_width, current_game_height);

	if (game_texture == NULL) {
		GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}

	return SUCCESS;
}

// 1. ASSETS: items, map

GAME_STATUS game_update(Game* game, real32 delta_time)
{
			
}


GAME_STATUS game_handle_events(Game* game)
{
		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				game->is_running = false;	 
			break;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					if (game__resize_texture(game_texture, game_renderer, event.window.data1, event.window.data2) != SUCCESS_CODE) {
						GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());	
						return SDL_FAILURE;
					}
					break;
				case SDL_WINDOWEVENT_EXPOSED:
					if (SDL_UpdateTexture(game_texture, NULL, game_surface->pixels, game_surface->pitch) < 0) {
						GAME_LOG_FATAL("Unable to update game texture: %s\n", SDL_GetError());	
						return SDL_FAILURE;
					}
					if (SDL_RenderClear(game_renderer) < 0) {
						GAME_LOG_FATAL("Unable to clear game renderer: %s\n", SDL_GetError());	
						return SDL_FAILURE;
					}
					if (SDL_RenderCopy(game_renderer, game_texture, NULL, NULL) < 0) {
						GAME_LOG_FATAL("Unable to copy to game renderer: %s\n", SDL_GetError());	
						return SDL_FAILURE;
					} 
					SDL_RenderPresent(game_renderer);
					break;
				break;
			 case SDL_KEYDOWN:
				// check for ctrl-q also, etc.
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					game->is_running = false;
				} else {
					game__system_input(game, event);
				}
			} 
		} 
	} 
	
}

GAME_STATUS game_start(Game* game, GAME_ArgTable* arg_table)
{
	GAME_ASSERT(game != NULL, "Game is null");	
	GAME_ASSERT(arg_table != NULL, "Argtable is null");	
		
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		GAME_LOG_FATAL("Unable to initialise game SDL backend: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	const char* window_title = GAME_UNAME" ["GAME_COMPILER" - x86/64]("GAME_BUILD_MODE")";
	game->window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									arg_table->width->value, arg_table->height->value, SDL_WINDOW_RESIZABLE);
	
	if (game->window == NULL) {
		GAME_LOG_FATAL("Unable to create game window: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	game->renderer = SDL_CreateRenderer(game_window, DEFAULT_RENDERING_DRIVER, GAME_SDL_NO_FLAGS);

	if (game->renderer == NULL) {
		GAME_LOG_FATAL("Unable to create game renderer: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	const int GAME_SURFACE_DEPTH = 32;
	// As we are type casting to specific values, endianness is important
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	const int RED_PIXEL_MASK = 0x00FF0000; 
	const int GREEN_PIXEL_MASK = 0x0000FF00;  
	const int BLUE_PIXEL_MASK = 0x000000FF;  
	const int ALPHA_PIXEL_MASK = 0xFF000000;  
#else
	const int RED_PIXEL_MASK = 0x00FF0000; 
	const int GREEN_PIXEL_MASK = 0x0000FF00;  
	const int BLUE_PIXEL_MASK = 0x000000FF;  
	const int ALPHA_PIXEL_MASK = 0xFF000000;  
#endif

	game_surface = SDL_CreateRGBSurface(GAME_SDL_NO_FLAGS, arg_table->width->value, arg_table->height->value, GAME_SURFACE_DEPTH
									0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	if (game_surface == NULL) {
		GAME_LOG_FATAL("Unable to create game surface: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	if (game__set_starting_surface(game_surface) == SURFACE_FAILURE_CODE) {
		GAME_LOG_FATAL("Unable to set starting game surface: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	game_texture = SDL_CreateTexture(game_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
											game_width, game_height);

	if (game_texture == NULL) {
		GAME_LOG_FATAL("Unable to create game texture: %s\n", SDL_GetError());	
		return SDL_FAILURE;
	}

	// create game->entity_manager

	game->is_running = true;

	return GAME_SUCCESS;
}

GAME_STATUS game_exit(Game* game, GAME_STATUS exit_status)
{
	if (game->entity_manager != NULL) game_entity_manager_destroy(game->entity_manager); 
	if (game->surface != NULL) SDL_FreeSurface(game->surface);
	if (game->texture != NULL) SDL_DestroyTexture(game->texture);
	if (game->renderer != NULL) SDL_DestroyRenderer(game->renderer);
	if (game->window != NULL) SDL_DestroyWindow(game->window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
	
	return exit_status;
}


