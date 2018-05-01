#include "core/game.h"
typedef struct {
	// renderer, surface, window, etc.	
} Game;
#include "core/texture.h"
#include "core/surface.h"
#include "core/events.h"

#include "common.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define PI32 3.14159265359f

GAME_STATUS game_update(Game* game, real32 delta_time)
{
			
}


GAME_STATUS game_handle_events(Game* game)
{
		GAME_STATUS game_events_handle_status = GAME_DEFAULT_INITIALISER;

		SDL_Event event = {0};
		while (SDL_PollEvent(&event)) {
			if ((game_events_handle_status = game_events__handle(game, event.type)) != SUCCESS) {
				GAME_LOG_FATAL("Unable to handle game events. Status %s\n", game_status_str(game_events_handle_status));	
				return FAILURE;
			}
		}

	return SUCCESS;
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
									RED_PIXEL_MASK, GREEN_PIXEL_MASK, BLUE_PIXEL_MASK, ALPHA_PIXEL_MASK);

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

	// load assets here??

	game->is_running = true;

	return GAME_SUCCESS;
}

void game_exit(Game* game)
{
	if (game->surface != NULL) SDL_FreeSurface(game->surface);
	if (game->texture != NULL) SDL_DestroyTexture(game->texture);
	if (game->renderer != NULL) SDL_DestroyRenderer(game->renderer);
	if (game->window != NULL) SDL_DestroyWindow(game->window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}


