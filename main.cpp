#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "Window.hpp"

//cheeky globals	
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

void keyPress(SDL_Event * event, float * dy)
{
	if(event->key.keysym.sym == SDLK_w)
	{
		if(*dy > -5)
		{
			*dy -= 5;
		}
	}
}

struct Pipe
{
	SDL_Rect upper;
	SDL_Rect lower;
};

void drawPipes(SDL_Renderer * renderer, Pipe * pipe, SDL_Texture * text)
{
	SDL_RenderCopy(renderer, text, nullptr, &pipe->lower);
	SDL_RenderCopyEx(renderer, text, nullptr, &pipe->upper, 0.0, nullptr,SDL_FLIP_VERTICAL);
};

Pipe makePipe(int gap, int heightOfBottom)
{
	Pipe p;
	
	p.lower.w = 32;
	p.lower.h = heightOfBottom;
	p.lower.y = SCREEN_HEIGHT - heightOfBottom;
	p.lower.x = SCREEN_WIDTH;
	
	p.upper.w = 32;
	p.upper.h = SCREEN_HEIGHT - heightOfBottom - gap;
	p.upper.y = 0;
	p.upper.x = SCREEN_WIDTH;
	
	return p;
}

void moveLeft(Pipe * pipe, int dx)
{
	pipe->upper.x -= dx;
	pipe->lower.x -= dx;

	if(pipe->upper.x < 0)
	{
		int gap = (rand() % (SCREEN_HEIGHT/4)) + SCREEN_HEIGHT/4;
		int height = (rand() % (SCREEN_HEIGHT/4)) + SCREEN_HEIGHT/4;
		*pipe = makePipe(gap, height);
	}
}

bool checkCollision(SDL_Rect * bird, Pipe * pipe)
{

}

int main()
{
	//variables for the window and the window itself
	const char * title = "flappy bird";
	bool running;
	SDL_Event event;
	Window window (title, SCREEN_WIDTH, SCREEN_HEIGHT, &running);

	//seed
	srand(time(nullptr));

	//load textures
	SDL_Texture * birdT = window.loadPNG("assets/bird.png");
	SDL_Texture * wingT = window.loadPNG("assets/wing.png");
	SDL_Texture * pipeT = window.loadPNG("assets/pipe.png");

	//game objects and logic
	const int framesPerSecond = 30;

	//bird stuff
	SDL_Rect birdPos = {32, 0, 64, 64};
	float dy = 0, y = 0;

	//pipe
	Pipe pipe = makePipe(100, 200);

	while(running)
	{
		//input
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					keyPress(&event, &dy);
					break;
			}
		}

		//updates

		//apply 'gravity'
		if(dy < 4)
		{
			dy += 0.1;
		}

		//update bird pos
		y += dy;
		birdPos.y = static_cast<int>(y);
		//update pipes
		moveLeft(&pipe, 1);

		//draw
		SDL_SetRenderDrawColor(window.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(window.renderer());
		SDL_RenderCopy(window.renderer(), birdT, nullptr, &birdPos);
		SDL_RenderCopyEx(window.renderer(), wingT, nullptr, &birdPos, 0.0, nullptr, (dy > 0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
		drawPipes(window.renderer(), &pipe, pipeT);

		//present
		SDL_RenderPresent(window.renderer());

		//block
		SDL_Delay(10);
	}


	return 0;
}
