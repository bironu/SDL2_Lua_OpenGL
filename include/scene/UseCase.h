#ifndef SCENE_USECASE_H_
#define SCENE_USECASE_H_

#include "misc/Uncopyable.h"

class Scene;
class UseCase
{
public:
	UNCOPYABLE(UseCase);
	UseCase(Scene &);
	virtual ~UseCase();

private:
	Scene &scene_;
};

#endif // SCENE_USECASE_H_
