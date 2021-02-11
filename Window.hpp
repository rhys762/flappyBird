#ifndef WINDOW_HPP
#define WINDOW_HPP

/*
 *	Rhys Trueman || 16/8/2020
 *
 *	SDL window and wrapper pair
 *	calls sdl init in its constructor, and sdl quit on its destruction
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window
{
	public:
		Window(const char * title, int width, int height, bool * success, int windowFlags=0, int renderFlags=SDL_RENDERER_ACCELERATED);
		~Window();

		//pointer to the renderer
		SDL_Renderer * renderer() const;

		//returns the windows pixel format
		Uint32 pixelFormat() const;
		
		//load a texture from a path
		SDL_Texture * loadPNG(const char * path);
	private:
		SDL_Window * mWindow;
		SDL_Renderer * mRenderer;

		int mWidth;
		int mHeight;
};

#endif
