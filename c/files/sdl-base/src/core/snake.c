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
  deque_push_back(segment_list, 5, 5);
  deque_push_back(segment_list, 5, 6);
  deque_push_back(segment_list, 5, 7);
}

int main(void)
{
  Snake snake;
}
