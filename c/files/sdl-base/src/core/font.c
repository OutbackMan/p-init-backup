// cell_width = font_width
// cell_height = font_height

TTF_Font* font = TTF_OpenFont("font.ttf", 16);
if (font == NULL) {
	// ...
}

void draw(x, y, character, colour)
{
	SDL_Rect rect {x,y,4,4};
	SDL_SetRenderDrawColor(m_render, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(m_render, &rect);		
}
