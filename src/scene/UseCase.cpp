#include "scene/UseCase.h"
#include "scene/Presenter.h"

UseCase::UseCase(Presenter &presenter)
	: presenter_(presenter)
{
}

UseCase::~UseCase()
{
}

void UseCase::exposed()
{
	presenter_.exposed();
}

void UseCase::finish()
{
	presenter_.finish();
}

void UseCase::quit()
{
	presenter_.quit();
}
