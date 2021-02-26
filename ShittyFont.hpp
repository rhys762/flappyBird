#ifndef SHITTYFONT_HPP
#define SHITTYFONT_HPP

/*
	Rhys Trueman || 14/02/2022

	This is pretty much what its named to be, a shitty font renderer.
	Dirty and quick because i found SDL2_ttf confusing and this seemed quicker (and the impression i got from ttf documentation was that it would be rendererd on a white background and i wanted transparent)
*/

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

		//update the source rect, returns true if it was a valid character, otherwise false
		bool fillSrcRect(char c);
};

#endif
