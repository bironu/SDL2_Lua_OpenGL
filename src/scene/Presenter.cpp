#include "scene/Presenter.h"
#include "scene/Scene.h"
#include "sdl/SDLWindow.h"
#include "app/Application.h"
#include "gl/widget/GLScreenView.h"
#include <SDL_opengl.h>

Presenter::Presenter(Scene &scene)
	: scene_(scene)
	, root_(std::make_shared<GL_::ScreenView>())
	, idling_(false)
{
}

Presenter::~Presenter()
{
}

void Presenter::update()
{
	scene_.update();
}

void Presenter::finish()
{
	scene_.finish();
}

void Presenter::quit()
{
	scene_.quit();
}

void Presenter::exposed()
{
	::glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::Enter2DMode();
	glTranslatef(0.0f, 0.0f, -1.0f);
	root_->draw();
	Scene::Leave2DMode();
	scene_.swap();
}
