static const size_t GAME_CHARACTER_GLYPH_DIMENSION = 8 * 8;

typedef enum {
	SOLID,
	EMPTY	
} GAME_GLYPH_FILL_TYPE;

typedef struct {
	GAME_GLYPH_FILL_TYPE matrix[GAME_CHARACTER_GLYPH_DIMENSION];
} GameCharacterGlyph;

typedef struct {
	SDL_Colour solid[1];
	SDL_Colour empty[1];
} GameCharacterPalette;

typedef struct {
	GameCharacterPalette palette[1];
	GameCharacterGlyph glyph[1];
} GameCharacter;

typedef struct {
	size_t width;
	size_t height;
	GameCharacter* characters;
} GameField;

// GameField game_field = {0};
// field_init(&game_field, 10, 10);
// field_set_pos(&game_field, CHARACTER_A, x, y); 
// field_set_pos(&game_field, sprite_person, x, y); 
// field_get_pos(&game_field, x, y);
// draw_field(&game_field); 

// set starting area
void field_init(GameField* field, size_t field_width, size_t field_height)
{
	GAME_XMALLOC(field->characters, sizeof(GameCharacter) * field_width * field_height);

	for (size_t field_row = 0; field_row < field_width; ++field_row) {
		for (size_t field_col = 0; field_col < field_height; ++field_col) {
			field->characters->palette->solid[0] = WHITE;
			field->characters->palette->empty[0] = BLACK;

			character_block_create(field->characters->glyph->matrix, COLOUR);
		}
	}	
}

void field_set_pos(GameField* field, CHARACTER_TYPE type, size_t x, size_t y, solid, empty)
{
	character_create_func_list[type](field->characters[y * width + x].glyph->matrix, solid, empty);
}

void draw_field_same_scale(GameField* field)
{
	// same scale assumes screen size is 8 times field width and height
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

	for (size_t field_row = 0; field_row < field->width; ++field_row) {
		for (size_t field_col = 0; field_col < field->height; ++field_col) {
			to_texture(character, x, y);
		}
	}

	to_texture()
	{
		for (size_t character_row = 0; character_row < 8; ++character_row) {
			for (size_t character_col = 0; character_col < 8; ++character_col) {
				size_t texture_coord = (field_col + character_col) * texture_width + field_row + character_row;
				texture_pixel[y + character_col + width * x + character_row] = colour[character_col * width + character_row]
			}	
		}
	}

	for (size_t texture_row = 0; texture_row < texture_width; ++texture_row) {
		texture_pixel = (u32 *)((u8 *)texture_pixels + texture_row * texture_pitch);
		for (size_t texture_col = 0; texture_col < texture_height; ++texture_col) {
			field_coord = texture_col * field_width + texture_row;
			
			for (size_t character_index = 0; character_index < 8 * 8; ++character_index) {
				if (field->characters[field_coord].glyph->matrix[character_index] == SOLID) {
					texture_pixel_colour = field->characters[field_coord].palette->solid;
				} else {
					texture_pixel_colour = field->characters[field_coord].palette->empty;
				}

				texture_pixel[texture_col * width + texture_row] =
				*texture_pixel++ = (
									(texture_pixel_colour->a << 24) |
									(texture_pixel_colour->r << 16) |
									(texture_pixel_colour->g << 8) | 
									(texture_pixel_colour->b)
								   ); 
			}
		}
	}

	SDL_UnlockTexture(game->texture);

}

public int[] resizePixels(int[] pixels,int w1,int h1,int w2,int h2) {
    int[] temp = new int[w2*h2] ;
    // EDIT: added +1 to account for an early rounding problem
    int x_ratio = (int)((w1<<16)/w2) +1;
    int y_ratio = (int)((h1<<16)/h2) +1;
    //int x_ratio = (int)((w1<<16)/w2) ;
    //int y_ratio = (int)((h1<<16)/h2) ;
    int x2, y2 ;
    for (int i=0;i<h2;i++) {
        for (int j=0;j<w2;j++) {
            x2 = ((j*x_ratio)>>16) ;
            y2 = ((i*y_ratio)>>16) ;
            temp[(i*w2)+j] = pixels[(y2*w1)+x2] ;
        }                
    }                
    return temp ;
}

void draw_field(GameField* field)
{
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
			
			for (size_t character_index = 0; character_index < 8 * 8; ++character_index) {
				if (field->characters[field_coord].glyph->matrix[character_index] == SOLID) {
					texture_pixel_colour = field->characters[field_coord].palette->solid;
				} else {
					texture_pixel_colour = field->characters[field_coord].palette->empty;
				}

				for (size_t width_scale_count = 0; width_scale_count < width_scale; ++width_scale_count) {
					*texture_pixel++ = (
										(texture_pixel_colour->a << 24) |
										(texture_pixel_colour->r << 16) |
										(texture_pixel_colour->g << 8) | 
										(texture_pixel_colour->b)
									   ); 
				}
			}
		}
	}

	SDL_UnlockTexture(game->texture);

}

void free_field(GameField* field)
{
	free(field->characters);	
}


// do ascii, and solid block
GameCharacter character_a = {
	SOLID, SOLID	
};

// frogger -> sprite (23:00)
