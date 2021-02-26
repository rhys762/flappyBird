#include "Bird.hpp"

//make the bird 'flap'
void flap(Bird * b)
{
	//we cant flap if were going terminal velocity upwards
	if(b->dy > -5)
	{
		//change the velocity
		b->dy -= 5;
		//flap tick is used in the animation
		b->flapTick = 10;
	}
}

//pull the dy to positive
void gravity(Bird * b)
{
	//only modify if we not going our terminal down velocity
	if(b->dy < 4)
	{
		b->dy += 0.3;
	}
}

//move the bird according to its dy
void move(Bird * b, int screenHeight)
{
	//update according to velocity
	b->y += b->dy;
	//make sure we havent gone above the screen
	if(b->y < 0)
	{
		b->y = 0;
		b->dy = 0;
	}
	//make sure we havent gone below the screen
	if(b->y > (screenHeight - b->boundingBox.h))
	{
		b->y = screenHeight - b->boundingBox.h;
		b->dy = 0;
	}
	//cast and apply to the bb
	b->boundingBox.y = static_cast<int>(b->y);
}

//draw the bird
void drawBird(SDL_Renderer * renderer, Bird * b, SDL_Texture * birdTexture, SDL_Texture * wingTexture)
{
	//we rotate the bird according to its vertical velocity
	//ie if the bird is going up its angled up(ish)
	double rotation = b->dy * 5;

	//bird
	SDL_RenderCopyEx(renderer, birdTexture, nullptr, &b->boundingBox, rotation, nullptr, SDL_FLIP_NONE);
	//bird wing
	SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
	if(b->flapTick)
	{
		flip = SDL_FLIP_NONE;
		b->flapTick--;
	}
	SDL_RenderCopyEx(renderer, wingTexture, nullptr, &b->boundingBox, rotation, nullptr, flip);
}
