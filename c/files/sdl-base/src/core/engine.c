// surface = SDL_LoadBMP("file.bmp");
// texture = SDL_CreateTextureFromSurface(surface);

// FOR FRAME SETTER --> for (uint32_t old_tick = SDL_GetTicks(); !is_running; ++old_tick)

#define COLOUR_RED { 255, 0, 0, 255 }
#define COLOUR_RED_THREEQUARTERS { 255, 0, 0, 200 }

typedef struct {
	size_t x;
	size_t y;
	size_t width;
	size_t height;
	int rotation;
	SDL_Colour* colours;
	SHAPE_FILL_TYPE* shape;
} Sprite;

void sprite_create(w, h)
{
	for (size_t index = 0; index < w * h; ++index) {
		s->colours[index] = COLOUR_BG;
	}	
}

void sprite_load(file_name)
{
	// put colours into s->colour array
	if (!load_file(file_name)) {
		sprite_create(8, 8);
	}	
}

// sprite_get_colour, sprite_sample_colour(floats??)
void sprite_set_colour(x, y, colour)
{
	s->colours[y * width + x] = colour;	
}

typedef struct {
	size_t width;
	size_t height;
	int* matrix;
} Field;


void draw(x, y, colour)
{
	SDL_SetRenderDrawColour(ren, colour);
	SDL_Rect block_draw = {
		.x = x * (win_w / field_w),
		.y = y * (win_w / field_w),
		.w = win_w / field_w,
		.h = win_w / field_w
	};
	SDL_RenderFillRect(ren, block_draw);
}

// draw_line can use this
void fill(x1, y1, x2, y2, colour)
{
	clip(x1, y1); clip(x2, y2);	
	SDL_SetRenderDrawColour(ren, colour);
	SDL_Rect block_draw = {
		.x = x1 * (win_w / field_w),
		.y = y1 * (win_w / field_w),
		.w = x2 * (win_w / field_w),
		.h = y2 * (win_w / field_w),
	};
	SDL_RenderFillRect(ren, block_draw);
}

void draw_string(x, y, str)
{
	// relate to sprite drawing	
}

// draw_circle, fill_circle

// draw_partial_sprite
void draw_sprite(x, y)
{
	draw(x + s_x, y + s_y, s->colour[s_x][s_y]);
}

// draw_wire_frame_model


int main(void)
{

}
