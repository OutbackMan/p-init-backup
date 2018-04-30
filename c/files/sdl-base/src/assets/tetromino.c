// typedef SDL_Colour colour_asset;
#include "sdl-colour-wrappers.h"

SDL_Color tetromino[7][16] = {0};

enum {
	TETROMINO_LEFT,
	TETROMINO_RIGHT
};

colour_asset* tetrominoes = NULL;
if (colours_assets__load_tetrominoes(tetrominoes)) {
	tetrominoes[TETROMINO_LEFT][TOP_LEFT];
}

GAME_STATUS game_assets__load_tetromino(colour_asset* tetromino)
{
	game_asset left_tetromino[16] = {
		RED, 		
	}
	// anything with BUF_PUSH requires __leave:
	BUF_PUSH(tetromino, left_tetromino);
	
}

void game_assets__free(colour_asset* asset_manager)
{
		BUF_FREE(asset_manager);	
}

tetromino[0] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR
};

tetromino[1] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[2] = {
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[3] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[4] = {
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR
};

tetromino[5] = {
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR,
	BG_COLOUR, BG_COLOUR, RED, BG_COLOUR
};

tetromino[6] = {
	BG_COLOUR, BG_COLOUR, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, RED, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR,
	BG_COLOUR, RED, BG_COLOUR, BG_COLOUR
};

