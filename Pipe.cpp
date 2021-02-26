#include "Pipe.hpp"

//draw the pipes to a rendererer
void drawPipes(SDL_Renderer * renderer, Pipe * pipe, SDL_Texture * text)
{
	//draw the bottom pipe
	SDL_RenderCopy(renderer, text, nullptr, &pipe->lower);
	//draw the top pipe
	SDL_RenderCopyEx(renderer, text, nullptr, &pipe->upper, 0.0, nullptr,SDL_FLIP_VERTICAL);
};

//fill a pipe struct with mostly random values
void makePipe(Pipe * p, int screenWidth, int screenHeight)
{
	//gap is the space between the top and bottom pipe
	int gap = (rand() % (screenHeight/4)) + screenHeight/4;
	//height of the bottom pipe
	int heightOfBottom = (rand() % (screenHeight/4)) + screenHeight/4;
	//width of the pipes
	const int width = 32;	

	p->lower.w = width;
	p->lower.h = heightOfBottom;
	p->lower.y = screenHeight - heightOfBottom;
	p->lower.x = screenWidth;
	
	p->upper.w = width;
	p->upper.h = screenHeight - heightOfBottom - gap;
	p->upper.y = 0;
	p->upper.x = screenWidth;
}

//move the pipe left by dx pixels, if it moves off the screen then 'reset it' with makePipe
void moveLeft(Pipe * pipe, int dx, int screenWidth, int screenHeight)
{
	pipe->upper.x -= dx;
	pipe->lower.x -= dx;

	if(pipe->upper.x < -pipe->upper.w)
	{
		makePipe(pipe, screenWidth , screenHeight);
	}
}
