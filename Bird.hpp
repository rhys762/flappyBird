#ifndef BIRD_HPP
#define BIRD_HPP

/*
	Rhys Trueman || 14/02/2021 

	Struct describing the player (a bird)
*/

#include <SDL2/SDL.h>

struct Bird
{
	//bounding box of the bird
	SDL_Rect boundingBox = {32, 0, 64, 64};
	//y position and change in y position respectively
	float y = 0, dy = 0;
	float dx = 0;
	//used in animation
	int flapTick = 0;
};

//make the bird 'flap'
void flap(Bird * b);
//pull the dy to positive
void gravity(Bird * b);
//move the bird according to its dy
void move(Bird * b, int screenHeight);
//draw the bird
void drawBird(SDL_Renderer * renderer, Bird * b, SDL_Texture * birdTexture, SDL_Texture * wingTexture);
#endif
