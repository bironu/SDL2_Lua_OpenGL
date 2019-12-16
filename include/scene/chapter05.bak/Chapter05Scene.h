#if !defined(SCENE_CHAPTER05_CHAPTER05SCENE_H_)
#define SCENE_CHAPTER05_CHAPTER05SCENE_H_

#include "../Scene.h"
#include <SDL2/SDL_stdinc.h>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>


namespace GL_
{
class Texture;
}

namespace chapter05
{

class Actor;
class SpriteComponent;
class Asteroid;
class Shader;
class VertexArray;
class Ship;
class Chapter05Scene: public Scene
{
public:
	explicit Chapter05Scene(Application &app, Resources &res, TaskManager &manager);
	virtual ~Chapter05Scene() override = default;

	virtual void dispatch(const SDL_Event &) override;
	virtual bool onIdle(uint32_t) override;
	virtual FuncCreateScene onSuspend() override;
	virtual void onCreate() override;
	virtual void onDestroy() override;
	void onResume(int);

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);
	
	std::shared_ptr<GL_::Texture> GetTexture(const std::string& fileName);
	
	// Game-specific (add/remove asteroid)
	void AddAsteroid(Asteroid* ast);
	void RemoveAsteroid(Asteroid* ast);
	std::vector<Asteroid*>& GetAsteroids() { return mAsteroids; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, std::shared_ptr<GL_::Texture>> mTextures;

	// All the actors in the game
	std::vector<Actor*> mActors;
	// Any pending actors
	std::vector<Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<SpriteComponent*> mSprites;

	// Sprite shader
	Shader* mSpriteShader;
	// Sprite vertex array
	VertexArray* mSpriteVerts;


	Uint32 mTicksCount;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	Ship* mShip;
	std::vector<Asteroid*> mAsteroids;
};

}

#endif // SCENE_CHAPTER05_CHAPTER05SCENE_H_
