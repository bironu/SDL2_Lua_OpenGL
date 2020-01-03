#include "gl/widget/GLViewGroup.h"
#include "gl/GLSprite.h"
#include <SDL2/SDL_opengl.h>

namespace GL_
{

ViewGroup::ViewGroup(XOrigin &xorigin, YOrigin &yorigin)
	: View(xorigin, yorigin)
	, children_()
	, back_()
{
}

ViewGroup::~ViewGroup()
{
	clearChild();
}

void ViewGroup::draw(std::shared_ptr<Shader> shader)
{
	for(auto view : children_){
		if (view->isVisible()) {
			view->draw(shader);
		}
	}
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
