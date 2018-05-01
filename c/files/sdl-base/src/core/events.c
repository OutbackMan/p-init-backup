GAME_STATUS game_events__handle(Game* game, SDL_Event* event)
{
	switch (event->type) {
	case SDL_QUIT:
		game->is_running = false;	 
		break;
	case SDL_WINDOWEVENT:
		handle_window_events(game, &event->window);
		break;
	case SDL_KEYDOWN:
		handle_keyboard_events(game, &event->key);
		break;
	GAME_NO_DEFAULT_CASE
	} 
}

GAME_INTERNAL GAME_STATUS handle_keyboard_events(Game* game, SDL_KeyboardEvent* keyboard_event)
{
	// check for ctrl-q also, etc.
	switch (keyboard_event->keysym.sym) {
		
	}
	if (event.key.keysym.sym == SDLK_ESCAPE) {
		game->is_running = false;
	} else {
		game__system_input(game, event);
	}
	
}

GAME_INTERNAL GAME_STATUS handle_window_events(Game* game, SDL_WindowEvent* window_event)
{
	switch (window_event->event) {
	case SDL_WINDOWEVENT_RESIZED:
		if (game_texture_resize(game->texture, game->renderer, window_event.data1, window_event.data2) != SUCCESS) {
			GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());	
			return SDL_FAILURE;
		}
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		if (SDL_UpdateTexture(game->texture, NULL, game_surface->pixels, game_surface->pitch) < 0) {
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
