#include "scene/Chapter05/Chapter05Scene.h"
// #include "sdl/SDLWindow.h"
// #include "gl/GLSprite.h"
// #include "gl/GLShader.h"
// #include "geo/Calculator.h"
// #include "app/Application.h"
// #include "resources/Resources.h"
// #include "resources/ImageId.h"
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_opengl.h>
// #include <SDL2/SDL_log.h>
#include "Game.h"

namespace Chapter05
{

Chapter05Scene::Chapter05Scene(Application &app, Resources &res, TaskManager &manager)
	: Scene(app, res, manager)
	, game_(std::make_shared<Game>())
{
}

void Chapter05Scene::dispatch(const SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		finish();
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_BACKSPACE:
			finish();
			break;

		case SDLK_ESCAPE:
			quit();
			break;
		break;

	default:
		break;
	}
}

bool Chapter05Scene::onIdle(uint32_t tick)
{
	game_->RunLoop();
	return true;
}

void Chapter05Scene::onCreate()
{
	Scene::onCreate();
	game_->Initialize();
}

void Chapter05Scene::onDestroy()
{
	game_->Shutdown();
	Scene::onDestroy();
}

void Chapter05Scene::onResume()
{
}

FuncCreateScene Chapter05Scene::onSuspend()
{
	return [](Application &app, Resources &res, TaskManager &manager){
		return std::make_shared<Chapter05Scene>(app, res, manager);
	};
}

}