#include "scene/menu/MenuScene.h"
#include "scene/menu/MenuController.h"
#include "scene/menu/MenuPresenter.h"
#include "scene/menu/MenuUseCase.h"
#include "app/Application.h"
#include "geo/Geometry.h"
#include "gl/GLTexture.h"
#include "sdl/SDLImage.h"
#include "sdl/SDLWindow.h"
#include "gl/widget/GLGroupView.h"
#include "gl/widget/GLImageView.h"
#include "gl/widget/GLScreenView.h"
#include "gl/widget/GLTextView.h"
#include "sdl/SDLTtfFont.h"
#include <SDL_events.h>
#include <SDL_opengl.h>

MenuScene::MenuScene(uint32_t windowId)
	: Scene(windowId)
	, dataStore_()
	, presenter_(*this, dataStore_)
	, useCase_(presenter_, dataStore_)
	, controller_(useCase_, dataStore_)
{
}

void MenuScene::dispatch(const SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F5) {
		reload();
	}
	controller_.dispatch(event);
}

bool MenuScene::onIdle(uint32_t tick)
{
	bool result = Scene::onIdle(tick);
	controller_.onIdle(tick);
	return result || controller_.isIdling() || presenter_.isIdling();
}

void MenuScene::onCreate()
{
	Scene::onCreate();
	controller_.setJoystickOption();
	useCase_.onCreate();
}

void MenuScene::onDestroy()
{
	controller_.clearJoystickOption();
	Scene::onDestroy();
}

void MenuScene::onAddJoystick(int index)
{
	controller_.setJoystickOption();
}

void MenuScene::onResume(int posMain, int posSub, bool mode)
{
	controller_.setJoystickOption();
	useCase_.onResume(posMain, posSub, mode);
}

std::shared_ptr<SceneResumeCommand> MenuScene::onSuspend()
{
	return std::make_shared<MenuSceneResumeCommand>(getWindow()->getWindowId(), useCase_.getMainMenuPos(), useCase_.getSubMenuPos(), useCase_.getMode());
}

void MenuScene::reload()
{
	dataStore_.reload();
	controller_.setJoystickOption();
	useCase_.onCreate();
}

std::shared_ptr<Scene> MenuSceneResumeCommand::resume() {
	auto result = std::make_shared<MenuScene>(windowId_);
	result->onResume(posMain_, posSub_, mode_);
	return result;
}

MenuSceneResumeCommand::MenuSceneResumeCommand(uint32_t windowId, int posMain, int posSub, bool mode)
	: windowId_(windowId)
	, posMain_(posMain)
	, posSub_(posSub)
	, mode_(mode)
{
}
