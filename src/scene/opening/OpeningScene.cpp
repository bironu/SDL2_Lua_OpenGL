#include "scene/opening/OpeningScene.h"
#include "scene/opening/OpeningController.h"
#include "scene/opening/OpeningPresenter.h"
#include "scene/opening/OpeningUseCase.h"
#include "sdl/SDLWindow.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>

OpeningScene::OpeningScene(Application &app, Resources &res, TaskManager &manager)
	: Scene(app, res, manager)
	, dataStore_(res)
	, presenter_()
	, useCase_()
	, controller_()
{
}

void OpeningScene::dispatch(const SDL_Event &event)
{
//	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F5) {
//		reload();
//	}
	controller_.dispatch(event);
}

bool OpeningScene::onIdle(uint32_t tick)
{
	controller_.onIdle(tick);
	bool result = Scene::onIdle(tick);
	return result || controller_.isIdling() || presenter_.isIdling();
}

void OpeningScene::onCreate()
{
	Scene::onCreate();
}

void OpeningScene::onDestroy()
{
	Scene::onDestroy();
}

void OpeningScene::onAddJoystick(int index)
{
}

void OpeningScene::onResume()
{
}

FuncCreateScene OpeningScene::onSuspend()
{
	const int pos = useCase_.getPos();
	return [pos](Application &app, Resources &res, TaskManager &manager){
		auto result = std::make_shared<OpeningScene>(app, res, manager);
		result->getUseCase().setPos(pos);
		return result;
	};
}
