#if !defined(GLVIEW_H_)
#define GLVIEW_H_

#include "geo/Vector2.h"
#include "geo/Vector3.h"
#include "math/Math.h"
#include "misc/Uncopyable.h"
#include <memory>

namespace GL_
{
class GroupView;
class View
{
public:
	UNCOPYABLE(View);
	View();
	virtual ~View() = default;

	void draw();

	void setParent(std::shared_ptr<GroupView> parent)	{ parent_ = parent; }
	std::shared_ptr<GroupView> getParent() const { return parent_.lock(); }
	void clearParent() { parent_.reset(); }

	const geo::Vector3f &getPos() const { return pos_; }
	float getXPos() const { return pos_.getX(); }
	float getYPos() const { return pos_.getY(); }
	float getZPos() const { return pos_.getZ(); }

	void setPos(const geo::Vector3f &pos) { pos_ = pos; }
	void setXPos(const float x) { pos_.setX(x); }
	void setYPos(const float y) { pos_.setY(y); }
	void setZPos(const float z) { pos_.setZ(z); }

	const geo::Sizef &getSize() const { return size_; }
	float getWidth() const { return size_.getWidth(); }
	float getHeight() const { return size_.getHeight(); }

	void setSize(const geo::Sizef &size) { size_ = size; }
	void setWidth(const float w) { size_.setWidth(w); }
	void setHeight(const float h) { size_.setHeight(h); }

	void alignLeft();
	void alignRight();
	void alignTop();
	void alignBottom();
	void centeringXPos();
	void centeringYPos();

	void matchParentWidth();
	void matchParentHeight();
	void matchParentSize();

	bool isVisible() const { return visible_; }
	void setVisiblity(bool visible) { visible_ = visible; }
	void show() { visible_ = true; }
	void hide() { visible_ = false; }

protected:
	virtual void onDraw() = 0;

private:
	std::weak_ptr<GroupView> parent_;
	geo::Vector3f pos_;
	geo::Sizef size_;
	bool visible_;
};

enum class ViewXAlign
{
	Left,
	Center,
	Right,
};

enum class ViewYAlign
{
	Top,
	Center,
	Bottom,
};

} // GL_

#endif // GLVIEW_H_
