#define CHARACTER_GLYPH_SIZE 8

typedef enum {
	SOLID,
	EMPTY	
} GAME_GLYPH_TYPE;

typedef struct {
	GAME_GLYPH_TYPE matrix[8 * 8];
} GameCharacterGlyph;

typedef struct {
	SDL_Colour solid_colour;
	SDL_Colour empty_colour;
} GAME_CharacterPalette;

typedef struct {
	GAME_CharacterPalette* palette;
	GAME_CharacterGlyph* glyph;
} GAME_Character;

typedef struct {
	GAME_Character characters[PLACEHOLDER];
} GAME_World;

// do ascii, and solid block
GAME_Character character_a = {
	SOLID, SOLID	
};

// frogger -> sprite (23:00)
