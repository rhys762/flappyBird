#ifndef SUN_HPP
#define SUN_HPP

/*
	Rhys Trueman || 14/02/2021

	struct representing the sun, a purely decorative object
*/

#include <SDL2/SDL.h>
#include <iostream>

struct Sun
{
	SDL_Rect pos = {0, 30, 32, 32};
	double rotation = 0;
};

//draw the sun to the renderer
void draw(SDL_Renderer * renderer, SDL_Texture * texture, Sun * s);

//move and rotate the sun
void move(Sun * s, int screenWidth);

#endif
