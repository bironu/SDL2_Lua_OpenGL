#include "scene/opening/OpeningScene.h"
#include "sdl/SDLWindow.h"
#include "gl/GLSprite.h"
#include "gl/GLShader.h"
#include "geo/Calculator.h"
#include "app/Application.h"
#include "resources/Resources.h"
#include "resources/ImageId.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_log.h>

OpeningScene::OpeningScene(Application &app, Resources &res, TaskManager &manager)
	: Scene(app, res, manager)
	, spriteShader_()
{
}

void OpeningScene::dispatch(const SDL_Event &event)
{
//	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F5) {
//		reload();
//	}
	switch (event.type)
	{
	case SDL_QUIT:
		finish();
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_BACKSPACE:
			finish();
			break;

		case SDLK_ESCAPE:
			quit();
			break;

		case SDLK_RIGHT:
			back_->setXPos(back_->getXPos() + 1.0f);
			break;

		case SDLK_LEFT:
			back_->setXPos(back_->getXPos() - 1.0f);
			break;
		}
		break;

	default:
		break;
	}
}

bool OpeningScene::onIdle(uint32_t tick)
{
	bool result = Scene::onIdle(tick);
	clear();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	spriteShader_->setActive();
	back_->draw(spriteShader_);
	swap();
	return true;
}

void OpeningScene::onCreate()
{
	Scene::onCreate();
	back_ = std::make_shared<GL_::Sprite>(getResources().getImage(ImageId::BackGround2));
	if (!loadShaders())
	{
		SDL_Log("Failed to load shaders.");
		getApplication().quit(1);
	}
}

void OpeningScene::onDestroy()
{
	spriteShader_->unload();
	spriteShader_.reset();
	Scene::onDestroy();
}

void OpeningScene::onResume()
{
}

bool OpeningScene::loadShaders()
{
	spriteShader_ = std::make_shared<GL_::Shader>();
	if (!spriteShader_->load("res/shaders/Sprite.vert", "res/shaders/Sprite.frag"))
	{
		return false;
	}

	spriteShader_->setActive();
	// Set the view-projection matrix
	const float sw = static_cast<float>(getResources().getScreenWidth());
	const float sh = static_cast<float>(getResources().getScreenHeight());

	const auto viewProj = geo::createSimpleViewProj(sw, sh);
	spriteShader_->setMatrixUniform("uViewProj", viewProj);
	return true;
}

FuncCreateScene OpeningScene::onSuspend()
{
	//const int pos = useCase_.getPos();
	// return [pos](Application &app, Resources &res, TaskManager &manager){
	// 	auto result = std::make_shared<OpeningScene>(app, res, manager);
	// 	result->getUseCase().setPos(pos);
	// 	return result;
	// };
	return [](Application &app, Resources &res, TaskManager &manager){
		return std::make_shared<OpeningScene>(app, res, manager);
	};
}
