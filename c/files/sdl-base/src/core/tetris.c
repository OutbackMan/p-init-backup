
static const size_t FIELD_WIDTH = 12;
static const size_t FIELD_HEIGHT = 25;
static const size_t VID_WIDTH = 40;

static const uint32_t Occ = 0x10000;

typedef struct {
  int field[FIELD_WIDTH][FIELD_HEIGHT];
} TetrisField;

typedef struct {
  
} TetrisPiece;

bool tetris_field_is_occupied(TetrisField* field, int x, int y)
{
  return (x < 1 || x > FIELD_WIDTH - 2 || (y >= 0 && field->field[y][x] & Occ));
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
  
  puts("game over");
}

void tetris_field_draw_block(TetrisField* field, int x, int y, int colour)
{

}
