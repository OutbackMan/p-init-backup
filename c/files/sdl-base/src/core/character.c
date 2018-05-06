static const size_t GAME_FIELD_CELL_SIZE = 8; // i.e. font size

typedef enum {
	EMPTY,
	LEFT_TETROMINO,
	RIGHT_TETROMINO
} GAME_FIELD_CELL_IDENTIFIER;

typedef struct {
	// Used to perform calculations
	GAME_FIELD_CELL_IDENTIFIER identifier;
	size_t width; // in relation to cell size, i.e. 2 means two cells
	size_t height;
	SDL_Texture* texture; // width * height
} GameSprite;

typedef struct {
	size_t width;
	size_t height;
	size_t cell_size;
	GAME_FIELD_IDENTIFIER* identifiers;
} GameField;

// GameField game_field = {0};
// field_init(&game_field, 10, 10);
// field_set_pos_sprite(&game_field, sprite, x, y);
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

void field_pos_set_sprite(GameField* field, GameMultiCell* multi_cell, size_t x, size_t y)
{
	for (size_t cell_row = 0; cell_row < multi_cell->width; ++cell_row) {
		for (size_t cell_col = 0; cell_col < multi_cell->height; ++cell_col) {
			field->identifiers[(y + cell_col) * field->width + (x + cell_row)] = multi_cell->identifier;
		} 
	} 		
}

void draw_field(GameField* field)
{
	int texture_width = GAME_DEFAULT_INITIALISER;
	int texture_height = GAME_DEFAULT_INITIALISER;

	SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);
	
	if (SDL_QueryTexture(game->texture, NULL, NULL, &texture_width, &texture_height) < 0) {
		GAME_LOG_FATAL("Unable to query game texture: %s\n", SDL_GetError());
		return SDL_FAILURE;
	}

	// ensure that window resize is a 'cell size' multiple of field_width and height
	int width_scale = texture_width / field->width;
	int height_scale = texture_height / field->height;

	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	
	for (size_t field_row = 0; field_row < field_width; ++field_row) {
		for (size_t field_col = 0; field_col < field_height; ++field_height) {
			SDL_Render
		
			field_coord = field_col * field_width + field_row;
		
			if (field[field_coord].identifier == GHOST) {
				src_rect = {
					.x = 0,
					.y = 0,
					.w = texture_width,
					.h = texture_height
				};
				
				dst_rect = {
					.x = field_row,
					.y = field_col,
					.w = texture_width * cell_width * width_scale,
					.h = texture_height * cell_height * height_scale
				};
				
				SDL_RenderCopy(renderer, texture, src_rect, dst_rect);
			}
		}
	}
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


void free_field(GameField* field)
{
	free(field->characters);	
}


// do ascii, and solid block
GameCharacter character_a = {
	SOLID, SOLID	
};

// frogger -> sprite (23:00)
