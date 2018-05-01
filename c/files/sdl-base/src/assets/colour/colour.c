#include <SDL2/SDL.h>

#define GAME_COLOUR_RED {255, 0, 0, 255}
#define GAME_BACKGROUND_COLOUR {255, 255, 255, 255}

void game_colour_asset_free(SDL_Colour* game_colour_asset)
{
	GAME_STRETCHY_BUF_FREE(colour_asset);	
}

INTERNAL inline u32 sdl_colour_to_bitmask(SDL_Colour* colour)
{
	return ((colour->a << 24) | (colour->r << 16) | 
				(colour->g << 8) | colour->b);	
}
