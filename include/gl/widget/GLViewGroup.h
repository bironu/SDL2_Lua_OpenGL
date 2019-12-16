#ifndef GLVIEWGROUP_H_
#define GLVIEWGROUP_H_

#include "GLView.h"
#include "sdl/SDLColor.h"
#include <list>

namespace GL_
{

class Texture;
class Sprite;
class ViewGroup: public View
{
public:
	ViewGroup();
	virtual ~ViewGroup() override;

	void removeChild(std::shared_ptr<View> child);
	void clearChild();
	std::list<std::shared_ptr<View>> &getChildren() { return children_; }
	void setBack(std::shared_ptr<Texture> back) ;

	static void addChild(std::shared_ptr<ViewGroup> parent, std::shared_ptr<View> child);

protected:
	virtual void onDraw() override;

private:
	void addChild(std::shared_ptr<View> child);

	std::list<std::shared_ptr<View>> children_;
	std::shared_ptr<Sprite> back_;
};

} // GL_

#endif // GLVIEWGROUP_H_