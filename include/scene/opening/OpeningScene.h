#ifndef SCENE_OPENING_OPENINGSCENE_H_
#define SCENE_OPENING_OPENINGSCENE_H_

#include "../Scene.h"
#include "OpeningController.h"
#include "OpeningDataStore.h"
#include "OpeningPresenter.h"
#include "OpeningUseCase.h"
#include <memory>

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
	virtual void onAddJoystick(int) override;
	virtual void onResume() override;

	OpeningDataStore &getDataStore() { return dataStore_; }
	OpeningPresenter &getPresenter() { return presenter_; }
	OpeningUseCase &getUseCase() { return useCase_; }
	OpeningController &getContoller() { return controller_; }

private:
	OpeningDataStore dataStore_;
	OpeningPresenter presenter_;
	OpeningUseCase useCase_;
	OpeningController controller_;
};

#endif // SCENE_OPENING_OPENINGSCENE_H_
