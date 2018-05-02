GAME_Character game_field[100 * 100];

typedef enum {
	SOLID,
	EMPTY
} GAME_CHAR_TYPE;

typedef struct {
	SDL_Colour desired_colour;
	int character[8 * 8];
} GAME_Character;

GAME_Character character_a = {
	SOLID, SOLID	
};
