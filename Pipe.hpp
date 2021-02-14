#ifndef PIPE_HPP
#define PIPE_HPP

#include <SDL2/SDL.h>

struct Pipe
{
	SDL_Rect upper;
	SDL_Rect lower;
};

//draw the pipes to a rendererer
void drawPipes(SDL_Renderer * renderer, Pipe * pipe, SDL_Texture * text);
//fill a pipe struct with mostly random values
void makePipe(Pipe * pipeOut, int screenWidth, int screenHeight);
//move the pipe left by dx pixels, if it moves off the screen then 'reset it' with makePipe
void moveLeft(Pipe * pipe, int dx, int screenWidth, int screenHeight);

#endif
