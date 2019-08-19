#include "../src/scene/chapter05/Shader.h" // TODO
#include "../src/scene/chapter05/VertexArray.h" // TODO
#include "../src/scene/chapter05/Math.h" // TODO
#include "scene/opening/OpeningPresenter.h"
#include "scene/opening/OpeningDataStore.h"
#include "scene/opening/OpeningScene.h"
#include "scene/menu/MenuScene.h"
#include "scene/chapter05/Chapter05Scene.h"
#include "app/Application.h"
#include "gl/GLUCompatible.h"
#include "sdl/SDLWindow.h"
#include "sdl/SDLTtfFont.h"
#include "sdl/SDLColor.h"
#include "gl/GLSprite2D.h"
#include "gl/GLSprite3D.h"
#include "sdl/SDLImage.h"
#include "gl/widget/GLTextView.h"
#include "gl/widget/GLScreenView.h"
#include "task/Interpolator.h"
#include "task/ActionTask.h"

#include <SDL2/SDL_opengl.h>

OpeningPresenter::OpeningPresenter(OpeningScene &scene, const OpeningDataStore &dataStore)
	: Presenter(scene)
	, scene_(scene)
	, dataStore_(dataStore)
	, listMenuItem_(dataStore_.getOpeningMenuItemList())
	, mixer_()
	, chunk_("res/sound/cursor7.wav")
	, mSpriteShader()
	, mSpriteVerts()
{
	auto root = getRootView();
	root->setBack(dataStore.getTextureScreenBack());

	auto fontSize = dataStore.getTitleFontSize();
	SDL_::TtfFont fontTitle(dataStore.getFontFileName(), fontSize);

	auto title = std::make_shared<GL_::TextView>();
	GL_::GroupView::addChild(root, title);
	title->setText(fontTitle, dataStore.getStringTitle(), SDL_::Color::WHITE);
	title->setWrapContentSize();
	title->centeringXPos();
	title->setYPos(100);

	init();
	mixer_.allocateChannels(listMenuItem_.size());

}

OpeningPresenter::~OpeningPresenter()
{
	if (mSpriteShader) {
		mSpriteShader->Unload();
	}
}

void OpeningPresenter::exposed()
{
	// ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Scene::Enter2DMode();
	// getRootView()->draw();
	// Scene::Leave2DMode();

	// Scene::Enter3DMode();
	// gluLookAtCompatible(
	// 		0.0f, 0.0f, 0.0f,
	// 		0.0f, 0.0f, -1.0f,
	// 		0.0f, 1.0f, 0.0f
	// );
	// glTranslated(0.0, 0.0, -40.0);
	// rotateMenu_.draw();
	// Scene::Leave3DMode();

	// Set the clear color to grey
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Draw all sprite components
	// Enable alpha blending on the color buffer
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Set shader/vao as active
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

		// Scale the quad by the width/height of texture
		// Matrix4 scaleMat = Matrix4::CreateScale(
		// 	static_cast<float>(mTexWidth),
		// 	static_cast<float>(mTexHeight),
		// 	1.0f);
		
		//Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		
		// Since all sprites use the same shader/vertices,
		// the game first sets them active before any sprite draws
		
		// Set world transform
		//shader->SetMatrixUniform("uWorldTransform", world);
		// Set current texture
		//mTexture->bind();
		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	scene_.swap();
}

bool OpeningPresenter::moveCursor(int oldPos, int newPos, bool isAnimation)
{
	const auto pair = rotateMenu_.computeDgrees(oldPos, newPos - oldPos, 100);
	const auto degrees = pair.first;
	const auto duration = pair.second;
	if (duration == 0) {
		return false;
	}

	scene_.unregisterTask(ID_ROTATE_MENU, false);
	if (isAnimation) {
		mixer_.playChannel(-1, chunk_, 0);
		auto animation = ActionTask::get();
		animation->setup(rotateMenu_.getDegrees(), degrees, duration, Application::getTickCount());
		animation->setInterpolator(InterpolatorFactory::create(InterpolatorType::AccelerateDecelerate));
		animation->setAction([this](double value) {
			rotateMenu_.setDegrees(value);
		});
		scene_.registerTask(ID_ROTATE_MENU, std::move(animation));
	}
	else {
		rotateMenu_.setDegrees(degrees);
	}
	return true;
}

void OpeningPresenter::action(uint32_t tick)
{
	setIdling(false);
	exposed();
}

void OpeningPresenter::startMenuScene()
{
	scene_.setNextScene(std::make_shared<MenuScene>(scene_.getWindow()->getWindowId()));
}

void OpeningPresenter::startChapter05Scene()
{
	scene_.setNextScene(std::make_shared<Chapter05Scene>(scene_.getWindow()->getWindowId()));
}

void OpeningPresenter::init()
{
	auto fontSize = dataStore_.getMenuFontSize();
	SDL_::TtfFont font(dataStore_.getFontFileName(), fontSize);

	rotateMenu_.clearMenuItem();
	rotateMenu_.setRadius(dataStore_.getRadius());
	for (auto item : listMenuItem_) {
		auto sprite = std::make_shared<GL_::Sprite3D>();
		auto imageMenuString = font.renderBlendedText(item, SDL_::Color::WHITE);
		sprite->setTexture(imageMenuString);
		sprite->setWidth(imageMenuString->getWidth() * 4 / imageMenuString->getHeight());
		sprite->setHeight(4.0);
		rotateMenu_.addMenuItem(sprite);
	}

	loadShaders();
	createSpriteVerts();
}

bool OpeningPresenter::loadShaders()
{
	mSpriteShader = std::make_shared<Shader>();
	if (!mSpriteShader->Load("Shaders/chapter05/Basic.vert", "Shaders/chapter05/Basic.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// Set the view-projection matrix
	//Matrix4 viewProj = Matrix4::CreateSimpleViewProj(dataStore_.getScreenWidth(), dataStore_.getScreenHeight());
	//mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void OpeningPresenter::createSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = std::make_shared<VertexArray>(vertices, 4, indices, 6);
}
