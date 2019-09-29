#ifndef SCENE_OPENING_OPENINGSCENE_H_
#define SCENE_OPENING_OPENINGSCENE_H_

#include "../Scene.h"
#include <memory>

namespace GL_
{
class Sprite;
class Shader;
}

class OpeningScene : public Scene
{
public:
	OpeningScene(Application &app, Resources &res, TaskManager &manager);
	virtual ~OpeningScene() override = default;

	virtual void dispatch(const SDL_Event &) override;
	virtual bool onIdle(uint32_t) override;
	virtual FuncCreateScene onSuspend() override;
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void onResume() override;

	// OpeningRepository &getRepository() { return repository_; }
	// OpeningPresenter &getPresenter() { return presenter_; }
	// OpeningUseCase &getUseCase() { return useCase_; }
	// OpeningController &getContoller() { return controller_; }

	bool loadShaders();

private:
	// OpeningRepository repository_;
	// OpeningPresenter presenter_;
	// OpeningUseCase useCase_;
	// OpeningController controller_;

	std::shared_ptr<GL_::Shader> spriteShader_;
	std::shared_ptr<GL_::Sprite> back_;
};

#endif // SCENE_OPENING_OPENINGSCENE_H_
