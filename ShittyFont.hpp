#ifndef SHITTYFONT_HPP
#define SHITTYFONT_HPP

#include <string>

#include "Window.hpp"

class ShittyFont
{
	public:
		//takes the renderer and the path to the png as arguements
		ShittyFont(Window * window, const char * pathToPng);

		//render to a x y position with width height the following text
		void renderFont(int xOffset, int yOffset, int widthHeight, const std::string & text);
	private:
		//a pointer to the renderer we render to
		SDL_Renderer * mRenderer;
		//pointer to the texture
		SDL_Texture * mFont;
		//rect used internally to as a source to grab from mFont
		SDL_Rect mSrcRect;
		//rect used as a destination on the renderer
		SDL_Rect mDestRect;

		//update the source rect
		bool fillSrcRect(char c);
};

#endif
