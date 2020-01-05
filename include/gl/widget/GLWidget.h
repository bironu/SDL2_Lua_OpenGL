#if !defined(GLWIDGET_H_)
#define GLWIDGET_H_

#include "gl/widget/GLViewOrigin.h"
#include "geo/AffineMap.h"
#include "misc/Uncopyable.h"
#include <memory>

namespace GL_
{
class Shader;
class ViewGroup;

class View
{
public:
	UNCOPYABLE(View);
	View(XOrigin &xorigin, YOrigin &yorigin);
	virtual ~View() = default;

	virtual void draw(std::shared_ptr<Shader> shader) = 0;

	void setParent(std::shared_ptr<ViewGroup> parent) { parent_ = parent; }
	std::shared_ptr<ViewGroup> getParent() const { return parent_.lock(); }
	void clearParent() { parent_.reset(); }

	const auto &getPos() const { return affine_.getPos(); }
	auto getXPos() const { return getPos().getX(); }
	auto getYPos() const { return getPos().getY(); }
	auto getZPos() const { return getPos().getZ(); }

	void setPos(const geo::Vector3f &pos) { affine_.setPos(pos); }
	void setXPos(const float x) { affine_.setXPos(x); }
	void setYPos(const float y) { affine_.setYPos(y); }
	void setZPos(const float z) { affine_.setZPos(z); }

	const geo::Sizef &getSize() const { return size_; }
	float getWidth() const { return size_.getWidth(); }
	float getHeight() const { return size_.getHeight(); }

	void setSize(const geo::Sizef &size) { size_ = size; }
	void setWidth(const float w) { size_.setWidth(w); }
	void setHeight(const float h) { size_.setHeight(h); }

	auto getScale() const { return affine_.getWidth(); }
	void setScale(const float s) { affine_.setWidth(s); affine_.setHeight(s); }

	bool isChange() const;
	const geo::Matrix4x4f &getMatrix();

	const XOrigin &getXOrigin() const { return xorigin_; }
	const YOrigin &getYOrigin() const { return yorigin_; }

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

private:
	std::weak_ptr<ViewGroup> parent_;
	geo::AffineMap affine_;
	geo::Matrix4x4f matrix_;
	geo::Sizef size_;
	bool visible_;
	XOrigin &xorigin_;
	YOrigin &yorigin_;
};

} // GL_

#endif // GLVIEW_H_
