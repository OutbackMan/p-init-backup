#include "assets/colour/colour.h"

STATUS_CODE game_surface__init(Game* game)
{
	SDL_Color bg_colour = BG_COLOUR;
#if SDL_BYTEORDER == SDL_BIGENDIAN

#endif
	u32 bg_bitmask = (bg_colour.a | (bg_colour.r << 16) | (bg_color.g << 8) | bg_color.b)

	if (SDL_MUSTLOCK(game_surface)) {
		if (SDL_LockSurface(game_surface) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to lock game surface: %s\n", SDL_GetError());	
			return SURFACE_FAILURE_CODE;
		}
	}

	for (int game_surface_row = 0; game_surface_row < game_width; ++game_surface_row) {
		game_surface_pixel = (u32 *)((u8 *)(game_surface_pixels) + game_surface_row * game_surface_pitch);
		for (int game_surface_col = 0; game_surface_col < game_height; ++game_surface_col) {
			if (UBORDER_COLLISION(game_surface_row, game_surface_col)) {
				*game_surface_pixel++ = bg_bitmask;
			}
		}
	}	

	if (SDL_MUSTLOCK(game_surface)) {
		SDL_UnlockSurface(game_surface);		
	}

	return SUCCESS_CODE;
}

INTERNAL STATUS_CODE game__set_surface_pixel_colour(SDL_Surface* game_surface, int x, int y, SDL_Color* colour)
{
	if (ASSERT_IF(game_surface != NULL && colour != NULL, "Null parameters")) {
		return INVALID_ARGUMENTS; 	
	}

	if (SDL_MUSTLOCK(game_surface)) {
		if (SDL_LockSurface(game_surface) < 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to lock game surface: %s\n", SDL_GetError());	
			return SURFACE_FAILURE_CODE;
		}
	}

	u8* surface_pixel = (u8 *)game_surface->pixels;
	surface_pixel += (y * game_surface->pitch) + (x * sizeof(u8));
	*surface_pixel = (colour->a | (colour->r << 16) | (colour->g << 8) | (colour->b));

	if (SDL_MUSTLOCK(game_surface)) {
		SDL_UnlockSurface(game_surface);		
	}

	return SUCCESS_CODE;
}

