#include "scene/opening/OpeningScene.h"
#include "scene/opening/VerticalRotateMenu.h"
#include "sdl/SDLWindow.h"
#include "gl/widget/GLSprite.h"
#include "gl/GLShader.h"
#include "gl/GLTexture.h"
#include "gl/view/GLViewGroup.h"
#include "gl/view/GLImageView.h"
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
	, spriteShader2D_()
	, spriteShader3D_()
	, back_()
	, image_()
	, menu_()
	, sprite_()
{
}

void OpeningScene::onCreate()
{
	Scene::onCreate();

	if (!loadShaders2D() || !loadShaders3D())	{
		SDL_Log("Failed to load shaders.");
		getApplication().quit(1);
	}

	auto &res = getResources();

	back_ = std::make_shared<GL_::ViewGroup>();
	back_->setWidth(static_cast<float>(res.getScreenWidth()));
	back_->setHeight(static_cast<float>(res.getScreenHeight()));
	back_->setZPos(-1.0f);
	image_ = std::make_shared<GL_::ImageView>(GL_::xcenter, GL_::ycenter);
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
	big->setAction([this](float value){
		image_->setScale(value);
	});
	big->setup(0.5, 1.5, 1000, tick);

	auto small = ActionTask::get();
	small->setInterpolator(InterpolatorFactory::create(InterpolatorType::AccelerateDecelerate));
	small->setAction([this](float value){
		image_->setScale(value);
	});
	small->setup(1.5, 0.5, 1000, tick);

	serial->addTask(big);
	serial->addTask(small);

	loop->setTask(serial);
	getManager().registerTask(0, loop);

	menu_ = std::make_shared<GL_::VerticalRotateMenu>();
	menu_->setRadius(0.5f);
	auto item1 = std::make_shared<GL_::Sprite>();
	item1->setTexture(res.getImage(ImageId::TextBack));
	auto item2 = std::make_shared<GL_::Sprite>();
	item2->setTexture(res.getImage(ImageId::TextBack));
	auto item3 = std::make_shared<GL_::Sprite>();
	item3->setTexture(res.getImage(ImageId::TextBack));
	
	GL_::WidgetGroup::addChild(menu_, item1);
	GL_::WidgetGroup::addChild(menu_, item2);
	GL_::WidgetGroup::addChild(menu_, item3);
	menu_->prepare();
	menu_->setZPos(-1.0f);

	loop = LoopTask::get();
	loop->setLoopCount(LoopTask::INFINIT);
	auto rotate = ActionTask::get();
	rotate->setInterpolator(InterpolatorFactory::create(InterpolatorType::AccelerateDecelerate));
	rotate->setAction([this](float value){
		menu_->setRotation(geo::Quaternionf::createRotater(degrees2radian(value), geo::Vector3f(1.0f, 0.0f, 0.0f)));
	});
	rotate->setup(0.0, 120.0, 1000, tick);
	loop->setTask(rotate);
	getManager().registerTask(1, loop);

	sprite_ = std::make_shared<GL_::Sprite>();
	sprite_->setTexture(res.getImage(ImageId::BackGround2));
}

bool OpeningScene::onIdle(uint32_t tick)
{
	bool result = Scene::onIdle(tick);
	clear();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto &res = getResources();
	spriteShader2D_->setActive();
	back_->draw(spriteShader2D_);

	::glClear(GL_DEPTH_BUFFER_BIT);

	// auto look = geo::createLookAt(
	// 	geo::Vector3f(0.0f, 0.0f, -1.0f),
	// 	geo::Vector3f(0.0f, 0.0f, 0.0f),
	// 	geo::Vector3f(0.0f, 1.0f, 0.0f)
	// );
	spriteShader3D_->setActive();
	sprite_->draw(spriteShader3D_);
	menu_->draw(spriteShader3D_);

	swap();
	return true;
}

void OpeningScene::onDestroy()
{
	getManager().unregisterTask(0, false);
	getManager().unregisterTask(1, false);
	spriteShader2D_->unload();
	spriteShader2D_.reset();
	spriteShader3D_->unload();
	spriteShader3D_.reset();
	Scene::onDestroy();
}

void OpeningScene::onResume()
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

		case SDLK_UP:
			sprite_->setZPos(sprite_->getZPos() - 0.5f);
			std::cout << "zpos = " << sprite_->getZPos() << std::endl;
			break;

		case SDLK_DOWN:
			sprite_->setZPos(sprite_->getZPos() + 0.5f);
			std::cout << "zpos = " << sprite_->getZPos() << std::endl;
			break;

		// case SDLK_RIGHT:
		// 	back_->setXPos(back_->getXPos() + 1.0f);
		// 	break;

		// case SDLK_LEFT:
		// 	back_->setXPos(back_->getXPos() - 1.0f);
		// 	break;

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


bool OpeningScene::loadShaders2D()
{
	spriteShader2D_ = std::make_shared<GL_::Shader>();
	if (!spriteShader2D_->load("res/shaders/Sprite.vert", "res/shaders/Sprite.frag"))
	{
		return false;
	}

	spriteShader2D_->setActive();
	auto &res = getResources();
	const float sw = static_cast<float>(res.getScreenWidth());
	const float sh = static_cast<float>(res.getScreenHeight());

	const auto viewProj = geo::createSimpleViewProj(sw, sh);
	spriteShader2D_->setMatrixUniform("uViewProj", viewProj);
	return true;
}

bool OpeningScene::loadShaders3D()
{
	spriteShader3D_ = std::make_shared<GL_::Shader>();
	if (!spriteShader3D_->load("res/shaders/Sprite.vert", "res/shaders/Sprite.frag"))
	{
		return false;
	}

	spriteShader3D_->setActive();
	// Set the view-projection matrix
	auto &res = getResources();
	const float sw = static_cast<float>(res.getScreenWidth());
	const float sh = static_cast<float>(res.getScreenHeight());

	const auto viewProj = geo::createPerspectiveFOV(degrees2radian(120.0f), sw, sh, 0.01f, 1000.0f);
	// const auto viewProj = geo::createOrtho(sw, sh, 1.0f, 1000.0f);
	spriteShader3D_->setMatrixUniform("uViewProj", viewProj);
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
