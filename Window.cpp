#include "Window.hpp"
#include <iostream>//error output

Window::Window(const char * title, int width, int height, bool * success, int windowFlags, int renderFlags)
:mWindow{nullptr}, mRenderer{nullptr}, mWidth{width}, mHeight{height}
{
	*success = false;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Could not init sdl: " << SDL_GetError() << std::endl;
	}
	else
	{

		mWindow = SDL_CreateWindow(title,
			       SDL_WINDOWPOS_UNDEFINED,	
			       SDL_WINDOWPOS_UNDEFINED,	
			       mWidth,
			       mHeight,
			       windowFlags);

		if(mWindow == nullptr)
		{
			std::cout << "could not create window: " << SDL_GetError() << std::endl;
		}
		else
		{
			int rendererMagicNumber = -1;//something to do with driver
			mRenderer = SDL_CreateRenderer(mWindow,
					rendererMagicNumber,
					renderFlags);

			if(mRenderer == nullptr)
			{
				std::cout << "Couldnt create renderer: " << SDL_GetError() << std::endl;
			}
			else
			{
				if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
				{
					std::cout << "couldnt initialize sdl_image";
				}
				else
				{
					*success = true;
				}
			}
		}
	}
}

Window::~Window()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

//pointer to the renderer
SDL_Renderer * Window::renderer() const
{
	return mRenderer;
}


//returns the windows pixel format
Uint32 Window::pixelFormat() const
{
	return SDL_GetWindowPixelFormat(mWindow);
}

//load a texture from a path
SDL_Texture * Window::loadPNG(const char * path)
{
	SDL_Surface * surf = nullptr;
	SDL_Texture * text = nullptr;
	
	surf = IMG_Load(path);
	text = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	return text;
}