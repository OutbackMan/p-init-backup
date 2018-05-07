int load_sprite(GameSprite* game_sprite, FILE* sprite_file)
{
	if (sprite_file != NULL) {
		static const size_t buf_size = 256;
		char buf[buf_size] = GAME_DEFAULT_INITIALISER;
		char* buf_handler = NULL;

		buf_handler = fgets(buf, sizeof(buf), sprite_file);
		if (buf_handler == NULL) {
			GAME_LOG_FATAL("Unable to read PPM file magic number");
			return FILE_FAILURE;		
		}
		if (strncmp(buf, "P6\n", 3) != 0) {
			GAME_LOG_FATAL("Non-raw PPM file format given for sprite conversion");
			return FILE_FAILURE;		
		}

		do {
			buf_handler = fgets(buf, sizeof(buf), sprite_file);		
			if (buf_handler == NULL) {
				GAME_LOG_FATAL("Unable to read PPM file comment section");
				return FILE_FAILURE;	
			}
		} while (strncmp(buf, "#", 1) == 0);
		
		int scan_count = GAME_DEFAULT_INITIALISER;

		scan_count = sscanf(buf, "%u %u", &game_sprite->width, &game_sprite->height);	
		if (scan_count < 2) {
			GAME_LOG_FATAL("Positive ASCII decimal values for PPM file width and height not found");
			return FILE_FAILURE;	
		}

		unsigned max_colour_value = GAME_DEFAULT_INITIALISER;
		scan_count = fscanf(sprite_file, "%u", &max_colour_value);
		if (scan_count < 1) {
			GAME_LOG_FATAL("Unable to read max colour value for PPM file");
			return FILE_FAILURE;	
		}
		if (max_colour_value != 255) {
			GAME_LOG_FATAL("Non RGB colour format detected for PPM file");
			return FILE_FAILURE;	
		}
		fseek(sprite_file, 1, SEEK_CUR);
		
		GAME_XMALLOC(sprite_file->colours, sizeof(GameCharacter) * sprite_file->width * sprite_file->height);

		u8 red_colour_component = GAME_DEFAULT_INITIALISER;
		u8 green_colour_component = GAME_DEFAULT_INITIALISER;
		u8 blue_colour_component = GAME_DEFAULT_INITIALISER;
		SDL_Colour character_colour = GAME_DEFAULT_INITIALISER;

		for (size_t pixel_index = 0; pixel_index < width * height; ++pixel_index) {
			fread(&red_colour_component, sizeof(u8), 1, sprite_file);
			fread(&green_colour_component, sizeof(u8), 1, sprite_file);
			fread(&blue_colour_component, sizeof(u8), 1, sprite_file);

			character_colour = {
				.r = red_colour_component,
				.g = green_colour_component,
				.b = blue_colour_component,
				.a = 255
			};

			*sprite_file->colours++ = character_colour;
		}

	return SUCCESS;
}

void free_sprite(GameSprite* game_sprite)
{
  free(game_sprite->characters);
}
