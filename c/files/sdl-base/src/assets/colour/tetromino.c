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

/* SDL_Colour colour_map[FIELD_BLOCK_TYPES__LEN] = {
	COLOUR_BLACK, // BOUNDARY
	...
}
*/

// load_tetromino_assets() could just do ".inc"
// init_playing_field() perhaps just an int array? (assume texture initialised)
// -> playing_field[y * field_width + x] = (row == 0 || row == width - 1 || col == 0 || col = height - 1) ? BOUNDARY : EMPTY;

// current_piece, current_rotation, current_x = field_width / 2, current_y
// speed (difficulty. say fall down every second, compute based on game ticks. if game ticks equal speed, fall down)
// piece_count (to control difficulty)
// score
// LOOP
// force_piece_down = (ticks == speed_ticks)
// update_playing_field()
// -> if (tetromino[current_piece][rotate(px, py, current_rotation)] == PIECE)
//		field[current_y + py * width + current_x + px] == PIECE
// handle_input() player, then game movement
// -> if (key_left && does_piece_fit(piece_id, current_rotation, current_x - 1, current_y))
//			current_x = current_x - 1;
//    if (key_z && key_z_not_previously_pressed && does_piece_fit(current_piece, current_rotation + 1, current_x, current_y)) necessary to latch rotate
// update()
// -> if (force_piece_down)
//		if (does_piece_fit(current_piece, current_rotation, current_x, current_y + 1)	
//			current_y++;
//		else
//			if (tetromino[current_piece][rotate(px, py, current_rotation) == PIECE)
//				field[current_y + py * width + current_x + px] = current_piece + 1; // assuming ordering
//				piece_count++; if (piece_count % 10 == 0) if (speed >= 10) speed--;
//			if (current_y + py < field_height - 1)
//				have_line &= (field[current_y + py * width + current_x + px]) != 0;	
//				if (have_line)
//					field[current_y + py * width + current_x + px] = LINE
//					lines.push(current_y + py)
//			score += 25; if (lines.not_empty) score += (1 << lines.size()) * 100;
//			current_x = width/2, current_y = 0, current_rotation = 0, current_piece = rand() % 7;
//			game_over = !does_piece_fit(current_piece, current_rotation, current_x, current_y);
// if (lines.not_empty)
//	draw_playing_field()
//	pause()
//	clear_line(), move_pieces_down();
// draw_score()
// draw_playing_field()
// -> convert_field_to_texture(): num-to-colour, 
// --> texture[y * width + x] = colour_map[field[y * width + x]];
// draw_texture() may have to have static window size
// LOOP
// printf("final score: %d\n", score);

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

bool game_assets_colour__tetromino_does_fit(int tetromino_id, int current_rotation, int top_left_x, int top_left_y)
{
	for (size_t px = 0; px < __Tetromino.width; ++px) {
		for (size_t py = 0; py < __Tetromino.height; ++py) {
			// piece index
			int pi = game_asset_colour__tetromino_rotation_index(top_left_x, top_left_y, current_rotation);		
			// field index
			int fi = (top_left_y + py) * field_width + (top_left_x + px);

			if (top_left_x + px >= 0 && top_left_x + px < field_width) {
				if (top_left_y + py >= 0 && top_left_y + py < field_height) {
					if (tetromino[tetromino_id][pi] == TETROMINO_PIECE && playing_field[fi] != EMPTY) {
						return false;		
					}
				}
			}
		}		
	}	
	return true;	
}

// observe code golf stackoverflow
