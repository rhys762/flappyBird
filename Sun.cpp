#include "Sun.hpp"

//draw the sun to the renderer
void draw(SDL_Renderer * renderer, SDL_Texture * texture, Sun * s)
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &s->pos, s->rotation, nullptr, SDL_FLIP_NONE);
}

//move and rotate the sun
void move(Sun * s, int screenWidth)
{
	s->pos.x = (s->pos.x + 1) % screenWidth;
	s->rotation += 1.0;
}
