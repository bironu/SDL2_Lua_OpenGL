#include "scene/opening/VerticalRotateMenu.h"
#include "gl/widget/GLSprite.h"
#include "geo/Calculator.h"
#include "geo/Quaternion.h"
#include "misc/Misc.h"
#include <SDL2/SDL_opengl.h>
#include <iostream>

namespace GL_ {

void VerticalRotateMenu::setDegrees(float degrees)
{
	while(true) {
		if (degrees < 0.0f) {
			degrees += MAX_DEGREES;
		}
		else if (MAX_DEGREES <= degrees) {
			degrees -= MAX_DEGREES;
		}
		else {
			break;
		}
	}
	degrees_ = degrees;
}

void VerticalRotateMenu::prepare()
{
	int n = 0;
	const auto radian = degrees2radian(MAX_DEGREES / step_);
	for (auto item : getChildren()) {
		const auto nradian = radian * n++;
		item->setXPos(0.0f);
		item->setYPos(radius_ * std::sin(nradian));
		item->setZPos(radius_ * std::cos(nradian));
		item->setRotation(geo::Quaternionf::createRotater(nradian, geo::Vector3f(1.0f, 0.0f, 0.0f)));

		std::cout << "n = " << n << ", ypos = " << item->getYPos() << ", zpos = " << item->getZPos() << std::endl;
	}
}

} // namespace GL_
