#ifndef SCENE_CHAPTER05_CHAPTER05SCENE_H_
#define SCENE_CHAPTER05_CHAPTER05SCENE_H_

#include "../Scene.h"
#include <memory>

namespace GL_
{
class Sprite;
class Shader;
}

namespace Chapter05
{
class Game;
class Chapter05Scene : public Scene
{
public:
	Chapter05Scene(Application &app, Resources &res, TaskManager &manager);
	virtual ~Chapter05Scene() override = default;

	virtual void dispatch(const SDL_Event &) override;
	virtual bool onIdle(uint32_t) override;
	virtual FuncCreateScene onSuspend() override;
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onResume() override;

private:
	std::shared_ptr<Game> game_;
};

} // Chapter05

#endif // SCENE_CHAPTER05_CHAPTER05SCENE_H_
