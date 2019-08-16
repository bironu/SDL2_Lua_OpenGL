#include "scene/chapter05/Chapter05Scene.h"
#include "app/Application.h"
#include "sdl/SDLWindow.h"
#include "sdl/SDLImage.h"
#include "gl/GLTexture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include <GL/glew.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_opengl.h>
#include <algorithm>

Chapter05Scene::Chapter05Scene(uint32_t windowId)
	: Scene(windowId)
{
}

void Chapter05Scene::dispatch(const SDL_Event &event)
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
		}
		break;

	default:
		break;
	}
}

bool Chapter05Scene::onIdle(uint32_t tick)
{
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	bool result = Scene::onIdle(tick);
	return true;
}

void Chapter05Scene::onCreate()
{
	Scene::onCreate();

	// Make sure we can create/compile shaders
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		Application::quit(1);
	}

	// Create quad for drawing sprites
	CreateSpriteVerts();

	LoadData();

	mTicksCount = SDL_GetTicks();
}

void Chapter05Scene::onDestroy()
{
	UnloadData();
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	Scene::onDestroy();
}

void Chapter05Scene::onAddJoystick(int index)
{
}

void Chapter05Scene::onResume(int pos)
{
}

std::shared_ptr<SceneResumeCommand> Chapter05Scene::onSuspend()
{
	return std::make_shared<Chapter05SceneResumeCommand>(getWindow()->getWindowId());
}

void Chapter05Scene::GenerateOutput()
{
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
	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	// Swap the buffers
	swap();
}

bool Chapter05Scene::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// Set the view-projection matrix
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Chapter05Scene::CreateSpriteVerts()
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

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Chapter05Scene::LoadData()
{
	// Create player's ship
	mShip = new Ship(this);
	mShip->SetRotation(Math::PiOver2);

	// Create asteroids
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Chapter05Scene::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	mTextures.clear();
}

std::shared_ptr<GL_::Texture> Chapter05Scene::GetTexture(const std::string& fileName)
{
	std::shared_ptr<GL_::Texture> tex;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	}
	else {
		auto image = std::make_shared<SDL_::Image>(fileName.c_str());
		if (image->isEnabled()) {
			tex = std::make_shared<GL_::Texture>(image);
			mTextures.emplace(fileName, tex);
		}
	}
	return tex;
}

void Chapter05Scene::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Chapter05Scene::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(),
		mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}

void Chapter05Scene::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Chapter05Scene::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Chapter05Scene::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Chapter05Scene::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}



std::shared_ptr<Scene> Chapter05SceneResumeCommand::resume() {
	auto result = std::make_shared<Chapter05Scene>(windowId_);
	return result;
}

Chapter05SceneResumeCommand::Chapter05SceneResumeCommand(uint32_t windowId)
	: windowId_(windowId)
{
}
