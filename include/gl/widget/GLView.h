#if !defined(GLVIEW_H_)
#define GLVIEW_H_

#include "geo/AffineMap.h"
#include "misc/Uncopyable.h"
#include <memory>

namespace GL_
{
class ViewGroup;
class View
{
public:
	UNCOPYABLE(View);
	View();
	virtual ~View() = default;

	void draw();

	void setParent(std::shared_ptr<ViewGroup> parent)	{ parent_ = parent; }
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

	const geo::Sizef getSize() const
	{
		return geo::Sizef{
			affine_.getWidth(),
			affine_.getHeight(),
		 };
	}
	float getWidth() const { return affine_.getWidth(); }
	float getHeight() const { return affine_.getHeight(); }

	void setSize(const geo::Sizef &size)
	{
		setWidth(size.getWidth());
		setHeight(size.getHeight());
	}
	void setWidth(const float w) { affine_.setWidth(w); }
	void setHeight(const float h) { affine_.setHeight(h); }

	bool isChange() const;
	const geo::Matrix4x4f getMatrix();

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
	std::weak_ptr<ViewGroup> parent_;
	geo::AffineMap affine_;
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
