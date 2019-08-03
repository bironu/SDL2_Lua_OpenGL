#include "sdl/SDLWindow.h"
#include "gl/widget/GLScreenView.h"
#include "resource/Resources.h"

namespace GL_
{

ScreenView::ScreenView()
	: GroupView()
{
	setXPos(0.0);
	setYPos(0.0);
	auto &res = Resources::instance();
	setWidth(res.getScreenWidth());
	setHeight(res.getScreenHeight());
}

} // GL_
