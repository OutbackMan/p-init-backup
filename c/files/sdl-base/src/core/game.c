#include "core/game.h"
typedef struct {
	// renderer, surface, window, etc.	
} Game;
#include "core/texture.h"
#include "core/surface.h"
#include "core/events.h"

#include "common.h"

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

	GameWorld game_world = GAME_DEFAULT_INITIALISER;
	// creates and loads starting map
	game__world_init(&game_world);

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

GAME_STATUS game_update(Game* game, real32 delta_time)
{
			
}

void game_exit(Game* game)
{
	if (game->surface != NULL) SDL_FreeSurface(game->surface);
	if (game->texture != NULL) SDL_DestroyTexture(game->texture);
	if (game->renderer != NULL) SDL_DestroyRenderer(game->renderer);
	if (game->window != NULL) SDL_DestroyWindow(game->window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
	// SDL_QuitSubSystem(); SDL_InitSubSystem();
}


