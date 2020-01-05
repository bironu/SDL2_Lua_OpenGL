#include "gl/view/GLView.h"
#include "gl/view/GLViewGroup.h"
#include "geo/Calculator.h"

namespace GL_ {

View::View(XOrigin &xorigin, YOrigin &yorigin)
	: parent_()
	, affine_()
	, matrix_(geo::createIdentityMatrix4x4<float>())
	, visible_(true)
	, xorigin_(xorigin)
	, yorigin_(yorigin)
{
}

void View::alignLeft()
{
	xorigin_.alignLeft(*this);
}

void View::alignRight()
{
	xorigin_.alignRight(*this);
}

void View::alignTop()
{
	yorigin_.alignTop(*this);
}

void View::alignBottom()
{
	yorigin_.alignBottom(*this);
}

void View::centeringXPos()
{
	xorigin_.centering(*this);
}

void View::centeringYPos()
{
	yorigin_.centering(*this);
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

const geo::Matrix4x4f &View::getMatrix()
{
	if (isChange()) {
		auto parent = getParent();
		if (parent) {
			matrix_ = parent->getMatrix() * affine_.getMatrix();
		}
		else {
			matrix_ = affine_.getMatrix();
		}
	}
	return matrix_;
}

} // GL_
