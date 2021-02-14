#include <iostream>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string>

#include "Window.hpp"
#include "Pipe.hpp"
#include "Bird.hpp"
#include "ShittyFont.hpp"
#include "Sun.hpp"

bool checkCollision(const SDL_Rect * a, const SDL_Rect * b)
{
	return !(
		a->y + a->h < b->y  ||//a is above b
		a->x >= b->x + b->w ||//a is to the right of b
		a->y >= b->y + b->h ||//a is below b
		a->x + a->w < b->x    //a is to the left of b
	);
}

bool checkCollision(const SDL_Rect * bird, const Pipe * pipe)
{
	return checkCollision(bird, &pipe->lower) || checkCollision(bird, &pipe->upper);
}

void setup(Pipe * p, Bird * b, int * score, int screenWidth, int screenHeight)
{
	makePipe(p, screenWidth, screenHeight);
	b->y = 0;
	b->dy = 0;
	b->dx = 3;
	*score = 0;
}

int main()
{
	//variables for the window and the window itself
	const char * title = "flappy bird";
	const int screenWidth = 400;
	const int gameHeight = 400;
	const int screenHeight = 500;
	bool running;
	SDL_Event event;

	Window window (title, screenWidth, screenHeight, &running);

	//seed
	srand(time(nullptr));

	//load textures and rects
	SDL_Texture * birdT = window.loadPNG("assets/bird.png");
	SDL_Texture * wingT = window.loadPNG("assets/wing.png");
	SDL_Texture * pipeT = window.loadPNG("assets/pipe.png");
	SDL_Texture * bgT = window.loadPNG("assets/bg.png");
	SDL_Texture * sunT = window.loadPNG("assets/sun.png");
	const SDL_Rect bg = {0, 0, screenWidth, gameHeight};
	const SDL_Rect bottomArea = {0, gameHeight, screenWidth, screenHeight - gameHeight};
	ShittyFont sf (&window, "assets/font.png");

	//timing variables
	const float framesPerSecond = 60;
	const float timePerFrame = 1000/framesPerSecond;
	float endOfLastFrame = SDL_GetTicks();
	float endOfThisFrame;
	float timeElapsed;

	//game stuff
	Bird bird;
	Pipe pipe;
	Sun sun;
	int score;
	auto setuplam = [&]()
	{
		setup(&pipe, &bird, &score, screenWidth, gameHeight);
		moveLeft(&pipe, -screenWidth, screenWidth, screenHeight);
	};
	setuplam();

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
					if(bird.dx)
					{
						flap(&bird);
					}
					else
					{
						if(event.key.keysym.sym == SDLK_r)
						{
							setuplam();
						}
					}
					break;
			}
		}

		//updates
		//apply 'gravity'
		gravity(&bird);
		//update bird pos
		move(&bird, gameHeight);
		//update pipes
		moveLeft(&pipe, bird.dx, screenWidth, gameHeight);
		//move sun
		move(&sun, screenWidth);
		//check collision
		if(checkCollision(&bird.boundingBox, &pipe))
		{
			bird.dx = 0;
		}		

		//draw
		//background
		SDL_RenderCopy(window.renderer(), bgT, nullptr, &bg);
		SDL_SetRenderDrawColor(window.renderer(), 0x40, 0x40, 0x40, 0xFF);
		SDL_RenderFillRect(window.renderer(), &bottomArea);
		//sun
		draw(window.renderer(), sunT, &sun);
		//draw the bird
		drawBird(window.renderer(), &bird, birdT, wingT); 
		//pipe
		drawPipes(window.renderer(), &pipe, pipeT);

		if(bird.dx)
		{
			sf.renderFont(20, gameHeight + 20, 32, std::to_string(score));
			sf.renderFont(20, gameHeight + 52, 16, "press any key to flap");
			score++;
		}
		else
		{
			sf.renderFont(10, gameHeight + 10, 16, "Game over press");
			sf.renderFont(10, gameHeight + 26, 16, "r to play again");
			sf.renderFont(10, gameHeight + 42, 16, "score " + std::to_string(score));
		}

		//present
		SDL_RenderPresent(window.renderer());

		//block
		endOfThisFrame = SDL_GetTicks();
		timeElapsed = endOfThisFrame - endOfLastFrame;
		if(timeElapsed < timePerFrame)
		{
			SDL_Delay(timePerFrame - timeElapsed);
			endOfThisFrame = SDL_GetTicks();
		}
		endOfLastFrame = endOfThisFrame;
	}


	return 0;
}
