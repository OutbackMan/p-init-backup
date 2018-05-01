#include "assets/colour/colour.h"

#include "assets/identifiers.h"
// typedef enum { EMPTY_SPACE, BORDER, TETROMINO } GAME_ASSET_IDENTIFIER;

static struct {
	size_t width;
	size_t height;
} __Tetromino = {
	.width = 4,
	.height = 4
};

GAME_STATUS game_assets_colour__tetromino_load(GAME_ASSET_IDENTIFIER* tetromino)
{
	GAME_STATUS leave_status = ENTERED;

	const size_t TETROMINO_DIMENSION = 16;

	GAME_ASSET_IDENTIFIER tetromino_1[TETROMINO_DIMENSION] = {
		EMPTY_SPACE, GAME_COLOUR_BG, 1_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		EMPTY_SPACE, GAME_COLOUR_BG, 1_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		EMPTY_SPACE, GAME_COLOUR_BG, 1_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		EMPTY_SPACE, GAME_COLOUR_BG, 1_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_1);

	SDL_Colour tetromino_Z[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, GAME_COLOUR_BG, Z_TETROMINO_COLOUR, GAME_COLOUR_BG,
		GAME_COLOUR_BG, Z_TETROMINO_COLOUR, Z_TETROMINO_COLOUR, GAME_COLOUR_BG,
		GAME_COLOUR_BG, Z_TETROMINO_COLOUR, GAME_COLOUR_BG, GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_Z);

	SDL_Colour tetromino_S[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, S_TETROMINO_COLOUR, GAME_COLOUR_BG, GAME_COLOUR_BG,
		GAME_COLOUR_BG, S_TETROMINO_COLOUR, S_TETROMINO_COLOUR, GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, S_TETROMINO_COLOUR, GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_S);

	SDL_Colour tetromino_O[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, O_TETROMINO_COLOUR, O_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, O_TETROMINO_COLOUR, O_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_COLOUR_BG, GAME_GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_O);

	SDL_Colour tetromino_T[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_T);

	SDL_Colour tetromino_vertical[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_vertical);
	SDL_Colour tetromino_vertical[TETROMINO_DIMENSION] = {
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG,
		GAME_COLOUR_BG, GAME_COLOUR_BG, LEFT_TETROMINO_COLOUR, GAME_GAME_COLOUR_BG
	}:
	BUF_PUSH(tetromino, tetromino_vertical);
	// have 0 for empty space, 1 for piece
		
	// anything with BUF_PUSH requires __leave:
	__leave:
		return leave_status;
	
}

// perhaps also a draw() function
// GAME_STATUS game_colour_assets__draw_tetromino(SDL_Surface, size_t scale)

// load_tetromino_assets()
// set_starting_surface()
// LOOP
// draw_active_surface() i.e. field
// 
// draw_surface_to_texture()
// LOOP

int game_assets_colour__tetromino_rotation_index(int x, int y, int rotation_index)
{
	switch (rotation_index % __Tetromino.width) {
	case 0:		
		return y * 4 + x; 
	case 1:		
		return 12 + y - (x * 4);
	case 2:		
		return 15 - (y * 4) - x;
	case 3:		
		return 3 - y + (x * 4);
	default:
		return 0;
	}
}

bool game_assets_colour__tetromino_does_fit(int tetromino, int current_rotation, int top_left_x, int top_left_y)
{
	for (size_t px = 0; px < __Tetromino.width; ++px) {
		for (size_t py = 0; py < __Tetromino.height; ++py) {
			// piece index
			int pi = game_asset_colour__tetromino_rotation_index(top_left_x, top_left_y, current_rotation);		
			// field index
		}		
	}	
	return true;	
}


