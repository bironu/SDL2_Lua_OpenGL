#include "gl/widget/GLView.h"
#include "gl/widget/GLViewGroup.h"
#include "task/Interpolator.h"

namespace GL_ {

View::View()
	: parent_()
	, visible_(true)
{
}

const geo::Vector3f View::getAbsolutePos() const
{
	return geo::Vector3f{
		getAbsoluteXPos(),
		getAbsoluteYPos(),
		getAbsoluteZPos()
	};
}

float View::getAbsoluteXPos() const
{
	auto x = getXPos();// + getMarginLeft();
	auto parent = getParent();
	if (parent) {
		x += parent->getAbsoluteXPos();
	}
	return x;
}

float View::getAbsoluteYPos() const
{
	auto y = getYPos();// + getMarginTop();
	auto parent = getParent();
	if (parent) {
		y += parent->getAbsoluteYPos();
	}
	return y;
}

float View::getAbsoluteZPos() const
{
	auto z = getYPos();// + getMarginTop();
	auto parent = getParent();
	if (parent) {
		z += parent->getAbsoluteYPos();
	}
	return z;
}

void View::alignLeft()
{
	setXPos(0);
}

void View::alignRight()
{
	auto parent = getParent();
	if (parent) {
		setXPos(parent->getWidth() - this->getWidth());
	}
}

void View::alignTop()
{
	setYPos(0);
}

void View::alignBottom()
{
	auto parent = getParent();
	if (parent) {
		setYPos(parent->getHeight() - this->getHeight());
	}
}

void View::centeringXPos()
{
	auto parent = getParent();
	if (parent) {
		setXPos((parent->getWidth()/2) - (this->getWidth()/2));
	}
}

void View::centeringYPos()
{
	auto parent = getParent();
	if (parent) {
		setYPos((parent->getHeight()/2) - (this->getHeight()/2));
	}
}

void View::draw()
{
	if (isVisible()) {
		onDraw();
	}
}

void View::matchParentWidth()
{
	auto parent = getParent();
	if (parent) {
		setWidth(parent->getWidth());
	}
}

void View::matchParentHeight()
{
	auto parent = getParent();
	if (parent) {
		setHeight(parent->getHeight());
	}
}

void View::matchParentSize()
{
	auto parent = getParent();
	if (parent) {
		setSize(parent->getSize());
	}
}

} // GL_
