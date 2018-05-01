STATUS_CODE game_texture__resize(Game* game, int current_game_width, int current_game_height)
{
	GAME_ASSERT(game != NULL, "msg");

	SDL_DestroyTexture(game->texture);	

	game->texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, current_game_width, current_game_height);

	if (game->texture == NULL) {
		GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}

	return SUCCESS;
}
