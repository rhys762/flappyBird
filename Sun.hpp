#ifndef SUN_HPP
#define SUN_HPP

#include <SDL2/SDL.h>
#include <iostream>

struct Sun
{
	SDL_Rect pos = {0, 30, 32, 32};
	double rotation = 0;
};

void draw(SDL_Renderer * renderer, SDL_Texture * texture, Sun * s)
{
	SDL_RenderCopyEx(renderer, texture, nullptr, &s->pos, s->rotation, nullptr, SDL_FLIP_NONE);
}

void move(Sun * s, int screenWidth)
{
	s->pos.x = (s->pos.x + 1) % screenWidth;
	s->rotation += 1.0;
}

#endif
