#ifndef SCENE_OPENING_OPENINGCONTROLLER_H_
#define SCENE_OPENING_OPENINGCONTROLLER_H_

#include "../Controller.h"

class OpeningController : public Controller
{
public:
	OpeningController();
	virtual ~OpeningController() override;

	virtual void onIdle(uint32_t) override;

private:
	virtual void onKeyDown(const SDL_KeyboardEvent &) override;
	virtual void onWindow(const SDL_WindowEvent &) override;
	virtual void onJoyButtonDown(const SDL_JoyButtonEvent &) override;
};

#endif // SCENE_OPENING_OPENINGCONTROLLER_H_
