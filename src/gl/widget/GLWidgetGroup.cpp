#include "gl/widget/GLWidgetGroup.h"

namespace GL_
{

void WidgetGroup::draw(std::shared_ptr<Shader> shader)
{
    if (!shader) {
        return;
    }

	for(auto widget : children_){
		if (widget->isVisible()) {
			widget->draw(shader);
		}
	}
}

void WidgetGroup::addChild(std::shared_ptr<Widget> child)
{
	children_.push_back(child);
}

void WidgetGroup::removeChild(std::shared_ptr<Widget> child)
{
	child->clearParent();
	children_.remove(child);
}

void WidgetGroup::clearChild()
{
	for (auto child : children_) {
		child->clearParent();
	}
	children_.clear();
}

void WidgetGroup::addChild(std::shared_ptr<WidgetGroup> parent, std::shared_ptr<Widget> child)
{
	parent->addChild(child);
	child->setParent(parent);
}

}