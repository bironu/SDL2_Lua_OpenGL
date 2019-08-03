#include "sdl/widget/SDLTextView.h"
#include "sdl/SDLRenderer.h"
#include "sdl/SDLTtfFont.h"
#include "sdl/SDLImage.h"
#include "sdl/SDLTexture.h"

namespace SDL_
{

void TextView::setText(Renderer &renderer, TtfFont &font, const char * const text, const Color &color)
{
	text_ = text;
	setSrc(renderer, font.renderBlendedText(text, color));
}

} // namespace SDL_
