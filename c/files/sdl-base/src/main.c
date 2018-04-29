#include "common.h"
#include "core/game.h"
#include "utils/log.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[argc + 1])
{
	GAME_STATUS leave_status = GAME_ENTERED;

#if defined(DEBUG_BUILD)
	game_log_init_logging((GAME_LOG_MODE)DEBUG_MODE, NULL);
#else
	FILE* game_log_file = fopen("game.log", "a");
	game_log_init_logging((GAME_LOG_MODE)RELEASE_MODE, game_log_file);
#endif
	
	const real32 DESIRED_FPS = 60.0f;
	const real32 DESIRED_FRAME_TIME = 1000.0f / DESIRED_FPS;
	
	GAME_ArgTable game_arg_table = game_arg_table_default_arg_table;
	GAME_STATUS game_arg_table_parse_status = GAME_DEFAULT_INITIALISER;
	if ((game_arg_table_parse_status = game_arg_table_parse(&game_arg_table)) != SUCCESS) {
		GAME_LOG_WARN("Unable to parse user supplied command line options for game. Using default values...\nStatus: %s", game_status_str(game_arg_table_parse_status));
	}
	
	const unsigned MAX_UPDATE_STEPS = 6;
	const real32 MAX_DELTA_TIME = 1.0f;

	u32 previous_frame_tick_count = SDL_GetTicks();

	Game game_instance = GAME_DEFAULT_INITIALISER;	

	GAME_STATUS game_start_status = GAME_DEFAULT_INITIALISER;
	if ((game_start_status = game_start(&game_instance, &game_arg_table)) != SUCCESS) {
		GAME_LOG_FATAL("Unable to start Game.\nStatus: %s", game_status_str(game_start_status));
		return EXIT_FAILURE;
	}

	while (game_is_running(&game)) {
		u32 current_frame_tick_count = SDL_GetTicks() - previous_frame_tick_count;
		previous_frame_tick_count = current_frame_tick_count;
		real32 total_delta_time = current_frame_tick_count / DESIRED_FRAME_TICK_COUNT;

		game_handle_events(&game);

		unsigned update_step_counter = 0;
		while (total_delta_time > 0.0f && update_step_counter < MAX_STEPS) {
			float delta_time = GAME_MIN_REAL32(total_delta_time, MAX_DELTA_TIME);
			total_delta_time -= delta_time;

			game_update(&game, delta_time);

			++update_step_counter;
		}

	}

	game_exit(&game);
	
#if defined(RELEASE_BUILD)
		if (game_log_file != NULL) {
			fclose(game_log_file);		
		}
#endif
	
	return EXIT_SUCCESS;

}
