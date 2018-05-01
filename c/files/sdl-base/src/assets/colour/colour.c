#include <SDL2/SDL.h>

#define GAME_COLOUR_BLACK {0, 0, 0, 255}
#define GAME_COLOUR_WHITE {255, 255, 255, 255}
#define GAME_COLOUR_GREY {128, 128, 128, 255}
#define GAME_COLOUR_RED {255, 0, 0, 255}
#define GAME_COLOUR_ORANGE {255, 165, 0, 255}
#define GAME_COLOUR_YELLOW {255, 255, 0, 255}
#define GAME_COLOUR_GREEN {0, 255, 0, 255}
#define GAME_COLOUR_BLUE {0, 0, 255, 255}
#define GAME_COLOUR_PURPLE {128, 0, 128, 255}
#define GAME_COLOUR_BROWN {139, 69, 19, 255}

#define GAME_BACKGROUND_COLOUR GAME_COLOUR_BLACK 

#if SDL_BYTEORDER == SDL_BIG_ENDIAN

void game_colour_asset_free(SDL_Colour* game_colour_asset)
{
	GAME_STRETCHY_BUF_FREE(colour_asset);	
}

INTERNAL inline u32 sdl_colour_to_bitmask(SDL_Colour* colour)
// SDL_MapRGB()
{
	return ((colour->a << 24) | (colour->r << 16) | 
				(colour->g << 8) | colour->b);	
}
