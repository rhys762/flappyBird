#include "ShittyFont.hpp"

//takes the renderer and the path to the png as arguements
ShittyFont::ShittyFont(Window * window, const char * pathToPng)
:mRenderer{window->renderer()}, mFont{window->loadPNG(pathToPng)}, mSrcRect{0, 0, 32, 32}, mDestRect{0,0,0,0}
{}

//render to a x y position with width height the following text
void ShittyFont::renderFont(int xOffset, int yOffset, int widthHeight, const std::string & text)
{
	mDestRect = {xOffset, yOffset, widthHeight, widthHeight};

	//for each character in text
	for(auto c : text)
	{
		//if it was a valid character
		if(fillSrcRect(c))
		{
			//draw it
			SDL_RenderCopy(mRenderer, mFont, &mSrcRect, &mDestRect);
		}
		//move the draw target onwards
		mDestRect.x += mDestRect.w;
	}
}

//update the source rect, returns true if it was a valid character, otherwise false
bool ShittyFont::fillSrcRect(char c)
{
	//this is hardcoded to the png
	if(c >= 'a' && c <= 'z')
	{
		c -= 'a';
	}
	else if(c >= 'A' && c <= 'Z')
	{
		c -= 'A';
	}
	else if(c >= '0' && c <= '9')
	{
		c -= '0';
		c += 26;
	}
	else
	{
		//invalid character
		return false;
	}
	mSrcRect.x = 32 * c;
	return true;
}
