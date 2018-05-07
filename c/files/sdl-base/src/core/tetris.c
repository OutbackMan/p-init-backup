static const size_t FIELD_WIDTH = 12;
static const size_t FIELD_HEIGHT = 25;

typedef struct {
	// array of enums 
} Field;

typedef struct {
	int x; // win_w / 2 - width / 2
	int y;
	int width;
	int height;
	int rotation;
	SDL_Colour* colours;
	SHAPE_FILL_TYPE* shape;
} Tetromino;

void tetromino_draw()
{
	for (size_t x = 0; x < t->width; ++x) {
		for (size_t y = 0; y < t->height; ++y) {
			if (t->shape[y * t->width + x] == FULL) {
				SDL_Colour block_colour = t->colours[y * t->width + x];	
				SDL_SetRenderDrawColour(ren, block_colour.r, block_colour.g, block_colour.b);	

				// to give 1px border, (x + 1), (y + 1), (w - 2), (h - 2)
				SDL_Rect block_draw = {
					.x = (t->x + x) * (win_w / field_w),
					.y = (t->y + y) * (win_w / field_w),
					.w = win_w / field_w,
					.h = win_w / field_w
				};
				SDL_RenderFillRect(ren, block_draw);
			}
	}
}

void move() {
	t->x += dx;
	t->y += dy;
}
// rotate_index()

void field_init(width, height)
{
  // set all to EMPTY
}

// when testing incrementally, run inside of debugger 
void render_field()
{
	// may have to include in separate file
  SDL_SetRenderDrawColour(ren, 0xff, 0xff, 0xff);
  SDL_RenderClear(ren);

  if (field[x][y] != PIECE) {
	SDL_RenderDrawPoint(ren, x * (win_w / field_w) + win_w / field_w / 2);
  } else {
	SDL_Rect block_draw = {
		.x = x * (win_w / field_w),
		.y = y * (win_w / field_w),
		.w = win_w / field_w,
		.h = win_w / field_w
	};
	SDL_RenderFillRect(ren, block_draw);
  }

  SDL_RenderPresent(render);
    
}

int main(void)
{
  field_init();
  for (bool is_running = true; !is_running; ) {
    
    render_field();
  }
  
  return 0;
}
