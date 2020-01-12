#if !defined(GLWIDGET_H_)
#define GLWIDGET_H_

#include "geo/AffineMap.h"
#include "misc/Uncopyable.h"
#include <memory>

namespace GL_
{
class Shader;
class WidgetGroup;

class Widget
{
public:
	UNCOPYABLE(Widget);
	Widget();
	virtual ~Widget() = default;

	virtual void draw(std::shared_ptr<Shader> shader) = 0;

	void setParent(std::shared_ptr<WidgetGroup> parent) { parent_ = parent; }
	std::shared_ptr<WidgetGroup> getParent() const { return parent_.lock(); }
	void clearParent() { parent_.reset(); }

	const auto &getPos() const { return affine_.getPos(); }
	auto getXPos() const { return getPos().getX(); }
	auto getYPos() const { return getPos().getY(); }
	auto getZPos() const { return getPos().getZ(); }

	void setPos(const geo::Vector3f &pos) { affine_.setPos(pos); }
	void setXPos(const float x) { affine_.setXPos(x); }
	void setYPos(const float y) { affine_.setYPos(y); }
	void setZPos(const float z) { affine_.setZPos(z); }

	const geo::Vector3f &getScale() const { return affine_.getScale(); }
	float getWidth() const { return affine_.getWidth(); }
	float getHeight() const { return affine_.getHeight(); }
	float getDepth() const { return affine_.getDepth(); }

	void setScale(const geo::Vector3f &scale) { affine_.setScale(scale); }
	void setWidth(const float width) { affine_.setWidth(width); }
	void setHeight(const float height) { affine_.setHeight(height); }
	void setDepth(const float depth) { affine_.setDepth(depth); }

	const auto &getOffset() const { return affine_.getOffset(); }
	const auto getXOffset() const { return affine_.getXOffset(); }
	const auto getYOffset() const { return affine_.getYOffset(); }
	const auto getZOffset() const { return affine_.getZOffset(); }

	void setOffset(const geo::Vector3f &offset) { affine_.setOffset(offset); }
	void setXOffset(const float x) { affine_.setXOffset(x); }
	void setYOffset(const float y) { affine_.setYOffset(y); }
	void setZOffset(const float z) { affine_.setZOffset(z); }

	void setRotation(const geo::Quaternionf &rotation) { affine_.setRotation(rotation); }
	void addRotation(const geo::Quaternionf &rotation) { affine_.addRotation(rotation); }
	void initRotation() { affine_.initRotation(); }

	bool isChange() const;
	const geo::Matrix4x4f &getMatrix();

	bool isVisible() const { return visible_; }
	void setVisiblity(bool visible) { visible_ = visible; }
	void show() { visible_ = true; }
	void hide() { visible_ = false; }

private:
	std::weak_ptr<WidgetGroup> parent_;
	geo::AffineMap affine_;
	geo::Matrix4x4f matrix_;
	bool visible_;
};

} // GL_

#endif // GLVIEW_H_
