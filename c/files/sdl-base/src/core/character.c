static const size_t GAME_FIELD_CELL_SIZE = 8; // i.e. font size

typedef enum {
	EMPTY,
	LEFT_TETROMINO,
	RIGHT_TETROMINO
} GAME_FIELD_CELL_IDENTIFIER;

typedef struct {
	// Used by render to determine type of object
	GAME_FIELD_CELL_IDENTIFIER identifier;
	size_t width; // in relation to cell size, i.e. 2 means two cells
	size_t height;
	SDL_Colour* colour_data; // width * height
} GameMultiCell;

typedef struct {
	GAME_FIELD_CELL_IDENTIFIER identifier;
	SDL_Colour* colour_data; // single colour
} GameSingleCell;

typedef struct {
	size_t width;
	size_t height;
	size_t cell_size;
	GAME_FIELD_IDENTIFIER* identifiers;
} GameField;

// GameField game_field = {0};
// field_init(&game_field, 10, 10);
// field_set_pos_multi_cell(&game_field, multi_cell, x, y);
// field_set_pos_single_cell(&game_field, single_cell, x, y);
// field_set_pos_identifier(&game_field, EMPTY, x, y); 
// field_get_pos_identifier(&game_field, x, y);
// draw_field(&game_field); 

// set starting area
void field_init(GameField* field, size_t field_width, size_t field_height, size_t cell_size)
{
	GAME_XMALLOC(field->identifiers, sizeof(GAME_FIELD_IDENTIFIER) * field_width * field_height);

	field->width = field_width;
	field->height = field_height;
	field->cell_size = cell_size;

	for (size_t field_row = 0; field_row < field_width; ++field_row) {
		for (size_t field_col = 0; field_col < field_height; ++field_col) {
			field->identifiers[field_col * field_width + field_row] = empty_single_cell->identifier;
		}
	}	
}

GAME_FIELD_IDENTIFIER field_pos_get_identifer(GameField* field, size_t x, size_t y)
{
	return field->identifiers[y * field->width + x];
}

void field_pos_set_multi_cell(GameField* field, GameMultiCell* multi_cell, size_t x, size_t y)
{
	for (size_t cell_row = 0; cell_row < multi_cell->width; ++cell_row) {
		for (size_t cell_col = 0; cell_col < multi_cell->height; ++cell_col) {
			field->identifiers[(y + cell_col) * field->width + (x + cell_row)] = multi_cell->identifier;
		} 
	} 		
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
