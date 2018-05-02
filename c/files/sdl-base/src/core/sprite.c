// Take base size of 'character' as 8 * 8 pixels

typedef struct {
  u32 width;
  u32 height;
  GameCharacter* characters;
} GameSprite;

// bmp loader






// ASSUME ALL BLOCK CHARACTERS
// width, height
// character_colour
int load_sprite(GameSprite* game_sprite, const char* sprite_file_name)
{
  FILE* sprite_file = fopen(sprite_file_name, "rb");
  if (sprite_file != NULL) {
    u32 game_sprite_width = GAME_DEFAULT_INITIALISER;
    u32 game_sprite_height = GAME_DEFAULT_INITIALISER;
    
    fread(&game_sprite_width, sizeof(game_sprite_width), 1, sprite_file);
    fread(&game_sprite_height, sizeof(game_sprite_height), 1, sprite_file);
    
    game_sprite->characters = xmalloc(sizeof(GameCharacter) * width * height);
    
   
  }
  
    
    
  
  
}

void destroy_sprite(GameSprite* game_sprite)
{
  free(game_sprite->characters);
}
