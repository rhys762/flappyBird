#ifndef MISC_HPP
#define MISC_HPP

/*
	Rhys Trueman || 26/02/2021

	Misc functions used in main, seperated for cleanliness
*/

#include <SDL2/SDL.h>

#include "Bird.hpp"
#include "Pipe.hpp"

//returns true if two rectangles are colliding
bool checkCollision(const SDL_Rect * a, const SDL_Rect * b);

//returns true if the bird is colliding with the pipe
bool checkCollision(const SDL_Rect * bird, const Pipe * pipe);

//called when the game restarts
void setup(Pipe * p, Bird * b, int * score, int screenWidth, int screenHeight);

#endif
