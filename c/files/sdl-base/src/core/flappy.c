// refer to makinggamessdl regarding sdl2 include
// #define SDL2() <SDL.h>
// #include SDL2()

// perhaps have (vim main.c | build) so can jump to error

typedef struct {
	SDL_Texture* bird_images;	
	int x;
	int y;
	bool is_rotated;
} Bird;

typedef struct {
		
} Pipe;

typedef struct {
	Pipe* pipe_list; // with stretchy buffers
} Game;


SDL_Rect bird = {
	.x = bird.x - bird_width / 2,
	.y = bird.y - bird_height / 2,
	.w = bird_width,
	.h = bird_height
};
if (SDL_IntersectRect(&bird, &pipe, &result))

void bird_draw()
{
	enum { BIRD_UP, BIRD_DOWN };
	// initially check it loads with SDL_RenderCopy(renderer, sprite, NULL, NULL)
	// SDL_RenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); to handle transparent pixels
	// change 4 times a second (SDL_GetTicks() % 400 > 200 ? bird1 : bird2)
}

int main(void)
{

	return 0;	
}
