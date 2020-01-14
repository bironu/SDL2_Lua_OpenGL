#include "gl/widget/GLWidget.h"
#include "gl/widget/GLWidgetGroup.h"
#include "geo/Calculator.h"

namespace GL_ {

Widget::Widget()
    : parent_()
    , affine_()
    , matrix_(geo::createIdentityMatrix4x4<float>())
    , visible_(true)
{
}

bool Widget::isChange() const
{
	bool result = affine_.isChange();
	if (!result) {
		auto parent = getParent();
		if (parent) {
			result |= parent->isChange();
		}
	}
	return result;
}

const geo::Matrix4x4f &Widget::getMatrix()
{
	//if (isChange() || isForceChange_) {
		auto parent = getParent();
		if (parent) {
			matrix_ = parent->getMatrix() * affine_.getMatrix();
		}
		else {
			matrix_ = affine_.getMatrix();
		}
	//}
	return matrix_;
}

} // GL_
