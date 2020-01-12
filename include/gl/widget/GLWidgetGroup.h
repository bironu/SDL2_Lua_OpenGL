#pragma once
#if !defined(GLWIDGETGROUP_H_)
#define GLWIDGETGROUP_H_

#include "gl/widget/GLWidget.h"
#include <list>

namespace GL_
{

class WidgetGroup : public Widget
{
public:
    WidgetGroup() : Widget() {}
    virtual ~WidgetGroup() override = default;

	virtual void draw(std::shared_ptr<Shader> shader) override;

	void removeChild(std::shared_ptr<Widget> child);
	void clearChild();
	std::list<std::shared_ptr<Widget>> &getChildren() { return children_; }

	static void addChild(std::shared_ptr<WidgetGroup> parent, std::shared_ptr<Widget> child);

private:
	void addChild(std::shared_ptr<Widget> child);

	std::list<std::shared_ptr<Widget>> children_;
};

}

#endif // GLWIDGETGROUP_H_
