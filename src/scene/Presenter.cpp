#include "scene/Presenter.h"
#include "scene/Scene.h"
#include "sdl/SDLWindow.h"
#include "app/Application.h"

Presenter::Presenter(Scene &scene)
	: scene_(scene)
	, idling_(false)
{
}

Presenter::~Presenter()
{
}