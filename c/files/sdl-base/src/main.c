#include "common.h"
#include "core/game.h"
#include "utils/log.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[argc + 1])
{
	int leave_status = GAME_DEFAULT_INITIALISER;

#if defined(DEBUG_BUILD)
	game__log_init_logging((GAME_LOG_MODE)DEBUG_MODE, NULL);
#else
	FILE* game_log_file = fopen("game.log", "a");
	game__log_init_logging((GAME_LOG_MODE)RELEASE_MODE, game_log_file);
#endif

	const unsigned MAX_UPDATE_STEPS = 6;
	const real32 DESIRED_FPS = 60.0f;
	const real32 DESIRED_FRAME_TIME = 1000.0f / DESIRED_FPS;
	const real32 MAX_DELTA_TIME = 1.0f;

	u32	previous_frame_tick_count = SDL_GetTicks();

	Game game = GAME_DEFAULT_INITIALISER;	

	int game_start_status = GAME_DEFAULT_INITIALISER;
	if ((game_start_status = game_start(&game)) != SUCCESS) {
		GAME_LOG_FATAL("Game unable to start! Status: %s", game_status_str(game_start_status));
		return EXIT_FAILURE;	
	}

	while (game_is_running(&game)) {
		u32 current_frame_tick_count = SDL_GetTicks() - previous_frame_tick_count;
		previous_frame_tick_count = current_frame_tick_count;
		real32 total_delta_time = current_frame_tick_count / DESIRED_FRAME_TICK_COUNT;

		game_handle_events(&game);

		unsigned update_step_counter = 0;
		while (total_delta_time > 0.0f && update_step_counter < MAX_STEPS) {
			float delta_time = min(total_delta_time, MAX_DELTA_TIME);
			total_delta_time -= delta_time;

			game_update(&game, delta_time);

			++update_step_counter;
		}

	}

	game_exit(&game);

// __leave:
#if defined(RELEASE_BUILD)
	if (game_log_file != NULL) {
		fclose(game_log_file);		
	}
#endif

	return EXIT_SUCCESS;
}
