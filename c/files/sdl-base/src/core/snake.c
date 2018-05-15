// create sprite sheet, (64 x 64) x 4
typedef struct {
  SDL_Texture* sprites;
  Deque segment_list;
} Snake;

void snake_create(Snake* snake)
{
  SDL_Surface* sprite_surface = SDL_LoadBMP("snake-sprites.bmp");
  sprites = SDL_CreateTextureFromSurface(sprite_surface);
  SDL_FreeSurface(sprite_surface);
  // coordinates
  deque_push_back(segment_list, 5, 5);
  deque_push_back(segment_list, 5, 6);
  deque_push_back(segment_list, 5, 7);
}

void snake_draw(Snake* snake)
{
	// sprite sheet indexes
	enum { HEAD_OPEN, TAIL, BODY, HEAD_CLOSED, FRUIT };
	// sprite sheet directions
	enum { LEFT. RIGHT, UP, DOWN };

	int sprite_base_rotations[SPRITE_COUNT][4] = {
		[HEAD_OPEN] = { [LEFT] = 0, [RIGHT] = 90 },
		[TAIL] = 90,
		[BODY] = -90
	};

	SDL_Rect src = {
		.w = SPRITE_WIDTH,
		.h = SPRITE_HEIGHT
	};

	SDL_Rect dst = {
		.w = SPRITE_WIDTH, // this can be larger or smaller
		.h = SPRITE_HEIGHT
	};

	int rotation = 0;
	for (size_t coord_index = 0; coord_index < deque_length; ++coord_index) {
		if (deque[coord_index].is_first) {
			src.x = HEAD_CLOSED * SPRITE_WIDTH;
			if (deque[coord_index].x == deque[coord_index + 1].x) {
				rotation = sprite_base_rotations[HEAD_CLOSED][LEFT];
			}

		} else if (deque[coord_index].is_last) {
			src.x = TAIL * SPRITE_WIDTH;
		} else {
			src.x = BODY * SPRITE_WIDTH;
		}
		dst.x = SPRITE_WIDTH * (deque.x + dx); // dx handled from keyboard
		dst.y = SPRITE_HEIGHT * (deque.y + dy);
	}

	SDL_RenderCopyEx(renderer, sprites, src, dst, rotation, NULL, SDL_FLIP_NONE);
}

void generate_fruit()
{
	fruit_x = rand() % (screen_width / SPRITE_WIDTH);
}

int main(void)
{
  Snake snake = {0};
  snake_create(&snake);
  snake_draw(&snake);
}
