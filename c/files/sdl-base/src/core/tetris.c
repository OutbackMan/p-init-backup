static const size_t FIELD_WIDTH = 12;
static const size_t FIELD_HEIGHT = 25;

typedef struct {
  
} Field;

typedef struct {

} Sprite;

void field_init(width, height)
{
  // set all to EMPTY
}

void render_field()
{
  SDL_SetRenderDrawColour(ren, 0xff, 0xff, 0xff);
  if (field[x][y] == PIECE) SDL_RenderDrawPoint(ren, x * (ren_wh / field_w) + ren_w / field_w / 2);
  else SDL_RenderDrawFill(ren, {x, y, w, h});
    
}

int main(void)
{
  field_init();
  for (bool is_running = true; !is_running; ) {
    
    render_field();
  }
  
  return 0;
}
