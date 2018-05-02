STATUS_CODE game_texture__resize(Game* game, int current_game_width, int current_game_height)
{
	GAME_ASSERT(game != NULL, "msg");

	SDL_DestroyTexture(game->texture);	

	game->texture = SDL_CreateTexture(
						game->renderer, 
						SDL_PIXELFORMAT_ARGB8888, 
						SDL_TEXTUREACCESS_STREAMING, 
						current_game_width, 
						current_game_height
					);
	if (game->texture == NULL) {
		GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}

	return SUCCESS;
}

STATUS_CODE field_to_texture(Game* game)
{
	GAME_ASSERT(game != NULL, "msg");
	
	int texture_width = GAME_DEFAULT_INITIALISER;
	int texture_height = GAME_DEFAULT_INITIALISER;

	if (SDL_QueryTexture(game->texture, NULL, NULL, &texture_width, &texture_height) < 0) {
		GAME_LOG_FATAL("Unable to query game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}

	// ensure that window resize is to an integer multiple of field_width
	int width_scale_factor = texture_width / field_width;
	int height_scale_factor = texture_height / field_height;

	void* texture_pixels = NULL;
	int texture_pitch = GAME_DEFAULT_INITIALISER;
	if (SDL_LockTexture(game->texture, NULL, &texture_pixels, &texture_pitch) < 0) {
		GAME_LOG_FATAL("Unable to query game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}
	
	u32* texture_pixel = NULL;
	SDL_Colour* texture_pixel_colour = NULL;
	size_t field_coord = GAME_DEFAULT_INITIALISER;

	for (size_t texture_row = 0; texture_row < texture_width; ++texture_row) {
		texture_pixel = (u32 *)((u8 *)texture_pixels + texture_row * texture_pitch);
		for (size_t texture_col = 0; texture_col < texture_height; ++texture_col) {
			field_coord = ((texture_col % height_scale) * field_width) + (texture_row % width_scale);

			texture_pixel_colour = colour_map[field[field_coord]];		

			*texture_pixel++ = (
								(texture_pixel_colour->a << 24) |
								(texture_pixel_colour->r << 16) |
								(texture_pixel_colour->g << 8) | 
								(texture_pixel_colour->b)
							   ); 
		}
	}

	SDL_UnlockTexture(game->texture);

}
