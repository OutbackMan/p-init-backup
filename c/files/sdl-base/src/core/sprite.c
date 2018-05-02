// Take base size of 'character' as 8 * 8 pixels

typedef struct {
  size_t width;
  size_t height;
  GameCharacter* characters;
} GameSprite;

int load_sprite(GameSprite* game_sprite, const char* sprite_file_name)
{
  FILE* sprite_file = fopen(sprite_file_name, "rb");
  if (sprite_file != NULL) {
  
  }
  
    
    
  game_sprite->characters = xmalloc(sizeof(GameCharacter) * width * height);
  
}

void destroy_sprite(GameSprite* game_sprite)
{
  free(game_sprite->characters);
}
