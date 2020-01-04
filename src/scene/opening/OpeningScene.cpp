#include "scene/opening/OpeningScene.h"
#include "sdl/SDLWindow.h"
#include "gl/GLSprite.h"
#include "gl/GLShader.h"
#include "gl/widget/GLViewGroup.h"
#include "gl/widget/GLImageView.h"
#include "geo/Calculator.h"
#include "app/Application.h"
#include "resources/Resources.h"
#include "resources/ImageId.h"
#include "task/TaskManager.h"
#include "task/ActionTask.h"
#include "task/LoopTask.h"
#include "task/SerialTask.h"
#include "task/Interpolator.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_log.h>

OpeningScene::OpeningScene(Application &app, Resources &res, TaskManager &manager)
	: Scene(app, res, manager)
	, spriteShader_()
	, back_()
	, image_()
{
}

void OpeningScene::dispatch(const SDL_Event &event)
{
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

		case SDLK_q:
			image_->alignLeft();
			image_->alignTop();
			break;
			
		case SDLK_w:
			image_->centeringXPos();
			image_->alignTop();
			break;

		case SDLK_e:
			image_->alignRight();
			image_->alignTop();
			break;

		case SDLK_a:
			image_->alignLeft();
			image_->centeringYPos();
			break;

		case SDLK_s:
			image_->centeringXPos();
			image_->centeringYPos();
			break;

		case SDLK_d:
			image_->alignRight();
			image_->centeringYPos();
			break;

		case SDLK_z:
			image_->alignLeft();
			image_->alignBottom();
			break;

		case SDLK_x:
			image_->centeringXPos();
			image_->alignBottom();
			break;

		case SDLK_c:
			image_->alignRight();
			image_->alignBottom();
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
	auto &res = getResources();

	back_ = std::make_shared<GL_::ViewGroup>();
	back_->setWidth(static_cast<float>(res.getScreenWidth()));
	back_->setHeight(static_cast<float>(res.getScreenHeight()));
	image_ = std::make_shared<GL_::ImageView>(GL_::xright, GL_::ybottom);
	GL_::ViewGroup::addChild(back_, image_);
	image_->setImage(res.getImage(ImageId::BackGround1));
	image_->centeringYPos();
	image_->centeringXPos();

	auto loop = LoopTask::get();
	loop->setLoopCount(LoopTask::INFINIT);

	auto serial = SerialTask::get();

	const auto tick = Application::getTickCount();

	auto big = ActionTask::get();
	big->setInterpolator(InterpolatorFactory::create(InterpolatorType::AccelerateDecelerate));
	big->setAction([this](double value){
		image_->setScale(value);
	});
	big->setup(0.5, 1.5, 1000, tick);


	auto small = ActionTask::get();
	small->setInterpolator(InterpolatorFactory::create(InterpolatorType::AccelerateDecelerate));
	small->setAction([this](double value){
		image_->setScale(value);
	});
	small->setup(1.5, 0.5, 1000, tick);

	serial->addTask(big);
	serial->addTask(small);

	loop->setTask(serial);
	getManager().registerTask(0, loop);

	if (!loadShaders())
	{
		SDL_Log("Failed to load shaders.");
		getApplication().quit(1);
	}
}

void OpeningScene::onDestroy()
{
	getManager().unregisterTask(0, false);
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
	auto &res = getResources();
	const float sw = static_cast<float>(res.getScreenWidth());
	const float sh = static_cast<float>(res.getScreenHeight());

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
