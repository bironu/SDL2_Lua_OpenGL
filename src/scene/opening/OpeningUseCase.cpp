#include "scene/opening/OpeningUseCase.h"

OpeningUseCase::OpeningUseCase()
	: UseCase()
	, pos_(0)
{
}

OpeningUseCase::~OpeningUseCase()
{
}

void OpeningUseCase::onCreate()
{
	setPos(0);
}

void OpeningUseCase::onResume(int pos)
{
	setPos(pos);
}

void OpeningUseCase::pushEnter()
{
	switch(getPos())
	{
	case 0:
		break;

	case 1:
		break;
	}
}

void OpeningUseCase::pushCancel()
{
}

void OpeningUseCase::pushUp()
{
	// const auto oldPos = pos_;
	// const auto newPos = --pos_;
	// if (pos_ < 0) {
	// 	pos_ = listMenuItem_.size() - 1;
	// }
	//presenter_.moveCursor(oldPos, newPos, true);
}

void OpeningUseCase::pushDown()
{
	// const auto oldPos = pos_;
	// const auto newPos = ++pos_;
	// if (pos_ >= static_cast<int>(listMenuItem_.size())) {
	// 	pos_ = 0;
	// }
	//presenter_.moveCursor(oldPos, newPos, true);
}

void OpeningUseCase::pushLeft()
{
}

void OpeningUseCase::pushRight()
{
}

void OpeningUseCase::action(uint32_t tick)
{
	//presenter_.action(tick);
}
