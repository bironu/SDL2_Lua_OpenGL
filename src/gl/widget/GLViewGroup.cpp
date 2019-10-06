#include "gl/widget/GLViewGroup.h"
#include "gl/GLSprite.h"
#include <SDL2/SDL_opengl.h>

namespace GL_
{

ViewGroup::ViewGroup()
	: View()
	, children_()
	, back_()
{
}

ViewGroup::~ViewGroup()
{
	clearChild();
}

void ViewGroup::onDraw()
{
	// ::glPushMatrix();
	// ::glTranslated(getXPos(), getYPos(), getZPos());
	// if (back_) {
	// 	back_->setXPos(0.0);
	// 	back_->setYPos(0.0);
	// 	back_->setZPos(0.0);
	// 	back_->setWidth(getWidth());
	// 	back_->setHeight(getHeight());
	// 	back_->draw();
	// }
	// for(auto view : children_){
	// 	view->draw();
	// }
	// ::glPopMatrix();
}

void ViewGroup::addChild(std::shared_ptr<View> child)
{
	children_.push_back(child);
}

void ViewGroup::removeChild(std::shared_ptr<View> child)
{
	child->clearParent();
	children_.remove(child);
}

void ViewGroup::clearChild()
{
	for (auto child : children_) {
		child->clearParent();
	}
	children_.clear();
}

void ViewGroup::addChild(std::shared_ptr<ViewGroup> parent, std::shared_ptr<View> child)
{
	parent->addChild(child);
	child->setParent(parent);
}

void ViewGroup::setBack(std::shared_ptr<Texture> texture)
{
	back_->setTexture(texture);
}

} // GL_
