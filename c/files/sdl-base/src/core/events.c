GAME_STATUS game_events__handle(Game* game, SDL_Event event)
{
			switch (event.type) {
			case SDL_QUIT:
				game->is_running = false;	 
			break;
			case SDL_WINDOWEVENT:
				handle_window_events(event.window.event);
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
GAME_INTERNAL GAME_STATUS handle_input_events(SDL_Event input_event)
{
	
}

GAME_INTERNAL GAME_STATUS handle_window_events(SDL_Event window_event)
{
				switch (window_event) {
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
}
