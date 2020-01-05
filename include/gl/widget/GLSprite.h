#ifndef GLSPRITE_H_
#define GLSPRITE_H_

#include "misc/Uncopyable.h"
#include "geo/Vector2.h"
#include "geo/Vector3.h"
#include "geo/AffineMap.h"
#include <memory>
#include <array>


namespace SDL_
{
class Image;
}

namespace GL_ {
class Shader;
class VertexArray;
class Texture;
class Sprite
{
public:
	UNCOPYABLE(Sprite);

	enum class XOrigin
	{
		Left,
		Center,
		Right,
	};

	enum class YOrigin
	{
		Top,
		Center,
		Bottom,
	};

	Sprite(XOrigin = XOrigin::Center, YOrigin = YOrigin::Center);
	~Sprite();

	void setTexture(std::shared_ptr<Texture>);
	void setTexture(std::shared_ptr<SDL_::Image>);
	void clearTexture();
	std::shared_ptr<Texture> getTexture() const { return texture_; }

	void draw(std::shared_ptr<Shader>);

	const auto &getPos() const { return affine_.getPos(); }
	auto getXPos() const { return getPos().getX(); }
	auto getYPos() const { return getPos().getY(); }
	auto getZPos() const { return getPos().getZ(); }

	const auto &getSize() const { return size_; }
	const auto getWidth() const { return size_.getWidth(); }
	const auto getHeight() const { return size_.getHeight(); }

	const auto &getOffset() const { return affine_.getOffset(); }
	const auto getXOffset() const { return affine_.getXOffset(); }
	const auto getYOffset() const { return affine_.getYOffset(); }
	const auto getZOffset() const { return affine_.getZOffset(); }

	void setPos(const geo::Vector3f &pos) { affine_.setPos(pos); }
	void setXPos(const float x) { affine_.setXPos(x); }
	void setYPos(const float y) { affine_.setYPos(y); }
	void setZPos(const float z) { affine_.setZPos(z); }

	void setSize(const geo::Sizef &size) { size_ = size; isChange_ = true; }
	void setWidth(const float w) { size_.setWidth(w); isChange_ = true; }
	void setHeight(const float h) { size_.setHeight(h); isChange_ = true; }

	void setOffset(const geo::Vector3f &offset) { affine_.setOffset(offset); }
	void setXOffset(const float x) { affine_.setXOffset(x); }
	void setYOffset(const float y) { affine_.setYOffset(y); }
	void setZOffset(const float z) { affine_.setZOffset(z); }

	void setAlpha(float alpha) { alpha_ = alpha; }
	float getAlpha() const { return alpha_; }

	auto getScale() const { return affine_.getWidth(); }
	void setScale(const float s) { affine_.setWidth(s); affine_.setHeight(s); }

	bool isChange() const { return affine_.isChange(); }
	const geo::Matrix4x4f &getMatrix();

private:
	std::shared_ptr<VertexArray> getSpriteVerts();

	std::shared_ptr<Texture> texture_;
	std::shared_ptr<VertexArray> vertexArray_;
	geo::AffineMap affine_;
	geo::Matrix4x4f matrix_;
	geo::Sizef size_;
	float alpha_;
	const XOrigin xorigin_;
	const YOrigin yorigin_;
	bool isChange_;
};

} // GL_

#endif // GLSPRITE_H_
