#include "misc.hpp"


//returns true if two rectangles are colliding
bool checkCollision(const SDL_Rect * a, const SDL_Rect * b)
{
	return !(
		a->y + a->h < b->y  ||//a is above b
		a->x >= b->x + b->w ||//a is to the right of b
		a->y >= b->y + b->h ||//a is below b
		a->x + a->w < b->x    //a is to the left of b
	);
}

//returns true if the bird is colliding with the pipe
bool checkCollision(const SDL_Rect * bird, const Pipe * pipe)
{
	return checkCollision(bird, &pipe->lower) || checkCollision(bird, &pipe->upper);
}

//called when the game restarts
void setup(Pipe * p, Bird * b, int * score, int screenWidth, int screenHeight)
{
	makePipe(p, screenWidth, screenHeight);
	b->y = 0;
	b->dy = 0;
	b->dx = 3;
	*score = 0;
}
