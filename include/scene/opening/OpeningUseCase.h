#ifndef SCENE_OPENING_OPENINGUSECASE_H_
#define SCENE_OPENING_OPENINGUSECASE_H_

#include "../UseCase.h"
#include <vector>
#include <string>

class OpeningUseCase : public UseCase
{
public:
	OpeningUseCase();
	virtual ~OpeningUseCase() override;

	void onCreate();
	void onResume(int);
	void pushEnter();
	void pushCancel();
	void pushUp();
	void pushDown();
	void pushLeft();
	void pushRight();
	void action(uint32_t);

	int getPos() const { return pos_; }
	void setPos(int pos) { pos_ = pos; }

private:
	int pos_;
};

#endif // SCENE_OPENING_OPENINGUSECASE_H_
