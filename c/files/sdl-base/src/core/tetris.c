
static const size_t FIELD_WIDTH = 12;
static const size_t FIELD_HEIGHT = 25;
static const size_t VID_WIDTH = 40;

static const uint32_t Occ = 0x10000;

typedef struct {
  FILL_TYPE field[FIELD_WIDTH][FIELD_HEIGHT];
} TetrisField;

typedef struct {
  int id;
  SPRITE_IDENTIFIER identifier;
  int width;
  int height;
  FILL_TYPE* shape;
  SDL_Colour colour;
} Sprite;

void draw_piece()
{
  draw_block(x, y, colour);
}

bool tetris_field_is_sprite_boundary(TetrisField* field, Sprite* sprite, int x, int y)
{
  return field->field[x][y] == sprite->identifier;
}

bool tetris_field_is_sprite_body(TetrisField* field, SPRITE_IDENTIFIER identifier, int x, int y)
{
  return field[x][y] == sprite->identifier && sprite->shape[x][y] == SOLID;
}

void tetris_field_draw_row(TetrisField* field, int y)
{
  for (int x = 1; x < FIELD_WIDTH - 1; ++x) tetris_field_draw_block(x, y, get(x));
}

void tetris_field_draw_block(TetrisField* field, int x, int y, int colour)
{
  if (x < FIELD_WIDTH && y < FIELD_HEIGHT) field->field[y][x] = colour;
  vid_mem[y * vid_width + x + render_x] = colour; // render_x defaults to zero
}

int main(void)
{
  for (int y = 0; y < FIELD_HEIGHT - 1; ++y) {
    draw_row(tetris_field, y);
  }
  
  // function for checking if solid pixel for each sprite
  
  for (bool is_running = true; !is_running; ) {
    for (int ren_x = 0, field_x = 0; field_x < field_w; ++field_x) {
      for (int ren_y = 0, field_y; field_y < field_h; ++field_y) {
        if (field[x][y] == PIECE) render_piece(field_x, &ren_x, field_y, &ren_y);
      }
    }
  }
  
  puts("game over");
}

void render_piece()
{
  for (int piece_x = 0; piece_x < piece_width; ++piece_x) {
    for (int scale_x_count = 0; scale_x_count < width_scale; ++scale_x_count) {
      for (int scale_y_count = 0; scale_y_count < height_scale; ++scale_y_count) {
        if (piece->shape[piece_x][piece_y]
        tex[field_y + ren_y * ren_width + field_x + ren_x] = piece->colour[piece_x][piece_y];
        *ren_y++;
      }
      *ren_x++;
  }
  *field_x += piece_width;
}
