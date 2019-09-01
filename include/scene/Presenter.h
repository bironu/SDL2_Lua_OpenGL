#ifndef SCENE_PRESENTER_H_
#define SCENE_PRESENTER_H_

#include "misc/Uncopyable.h"
#include <memory>

class Scene;
class Presenter
{
public:
	UNCOPYABLE(Presenter);
	Presenter(Scene &);
	virtual ~Presenter();
	virtual void exposed() = 0;
	bool isIdling() const { return idling_; }

protected:
	void setIdling(bool idling) { idling_ = idling; }

private:
	Scene &scene_;
	bool idling_;
};

#endif // SCENE_MENU_MENUPRESENTER_H_
