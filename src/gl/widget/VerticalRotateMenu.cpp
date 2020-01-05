#include "gl/widget/VerticalRotateMenu.h"
#include "gl/widget/GLSprite.h"
#include "geo/Calculator.h"
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
	for (auto item : listMenuItem_) {
		const auto nradian = radian * n++;
		item->setXPos(0.0f);
		item->setYPos(radius_ * std::sin(nradian));
		item->setZPos(radius_ * std::cos(nradian));
		
	}
}

std::shared_ptr<Sprite> VerticalRotateMenu::getMenuItem(int index)
{
	if (0 <= index && index < getMenuItemListSize()) {
		return listMenuItem_[index];
	}
	else {
		return std::shared_ptr<Sprite>();
	}
}

void VerticalRotateMenu::draw(std::shared_ptr<Shader> shader)
{
	auto &listMenuItem = getMenuItemList();
	if (listMenuItem.empty()) {
		return;
	}

	// //std::cout << "vertical rotate menu current degrees = " << getDegrees() << std::endl;
	// glRotated(getDegrees(), 1.0, 0.0, 0.0);

	if (!shader) {
		return;
	}

	// auto scale = geo::createScale(getWidth(), getHeight(), 1.0f);
	// shader->setMatrixUniform("uWorldTransform", getMatrix() * scale);
	// texture_->bind();
	// getSpriteVerts()->SetActive();
	// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	// const double deltaDegrees = 360.0 / listMenuItem.size();
	// for (auto item : listMenuItem) {
	// 	item->setXPos(0.0);
	// 	item->setYPos(0.0);
	// 	item->setZPos(getRadius());
	// 	item->draw();
	// 	glRotated(deltaDegrees, 1.0, 0.0, 0.0);
	// }
}

} // namespace GL_
