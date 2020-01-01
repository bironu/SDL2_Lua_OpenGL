#include "gl/widget/GLView.h"
#include "gl/widget/GLViewGroup.h"
#include "task/Interpolator.h"

namespace GL_ {

View::View()
	: parent_()
	, affine_()
	, visible_(true)
{
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

bool View::isChange() const
{
	bool result = affine_.isChange();
	auto parent = getParent();
	if (parent) {
		result |= parent->isChange();
	}
	return result;
}

const geo::Matrix4x4f View::getMatrix()
{
	auto result = affine_.getMatrix();
	auto parent = getParent();
	if (parent) {
		result = parent->getMatrix() * result;
	}
	return result;
}

} // GL_
