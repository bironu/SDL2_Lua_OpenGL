#pragma once
#ifndef GLVIEWGROUP_H_
#define GLVIEWGROUP_H_

#include "GLView.h"
#include <list>

namespace GL_
{

class Texture;
class Sprite;
class Shader;

class ViewGroup: public View
{
public:
	ViewGroup(XOrigin &xorigin = xcenter, YOrigin &yorigin = ycenter);
	virtual ~ViewGroup() override;

	virtual void draw(std::shared_ptr<Shader> shader) override;

	void removeChild(std::shared_ptr<View> child);
	void clearChild();
	std::list<std::shared_ptr<View>> &getChildren() { return children_; }

	static void addChild(std::shared_ptr<ViewGroup> parent, std::shared_ptr<View> child);

private:
	void addChild(std::shared_ptr<View> child);

	std::list<std::shared_ptr<View>> children_;
};

} // GL_

#endif // GLVIEWGROUP_H_
