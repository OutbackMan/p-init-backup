int unit_width = 16;
int unit_height = 16;

int level_width = 64;
int level_height = 16;
int level[level_width * level_height];

// at a minimum, we want (200, 200) tiles shown at (8, 8)

int tile_width = 8;
int tile_height = 8;

SDL_RenderSetLogicalSize(renderer, base_screen_width, base_screen_height);

// drawing map we add camera offset
// drawing objects we subtract to bring them back into viewable space

// may have to check if_focused() when handling input
int main(void)
{
  for (int x = 0; x < level_width; ++x) {
    for (int y = 0; y < level_height; ++y) {
      switch (level[y * level_width + x]) {
      case BLOCK:
		render_texture(texture, x)
        render_sprite(sprite_sheet, sprite_index, )
      }
    }
  }


}
int x_tiles_shown = 128;
int y_tiles_shown = 128;

void render_texture()
{
	tile_width = visible_unit_tiles / 
	SDL_Rect dst = {
		.x = x + scale_x,
		.y = y + scale_y,
		.w = scale_x,
		.h = scale_h
	};

	render(texture, src, s   	
}
