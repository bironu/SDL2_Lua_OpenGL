#include "gl/widget/GLTextView.h"
#include "sdl//SDLTtfFont.h"
#include "sdl/SDLImage.h"
#include "gl/GLTexture.h"

namespace GL_
{

void TextView::setText(SDL_::TtfFont &font, const char * const text, const Color &color)
{
	text_ = text;
	setSrc(font.renderBlendedText(text, color));
}

} // GL_
