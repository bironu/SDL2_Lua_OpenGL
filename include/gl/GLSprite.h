#ifndef GLSPRITE_H_
#define GLSPRITE_H_

#include "misc/Uncopyable.h"
#include "geo/Vector2.h"
#include "geo/Vector3.h"
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

	Sprite(std::shared_ptr<Texture>, XOrigin, YOrigin);
	Sprite(std::shared_ptr<SDL_::Image>, XOrigin, YOrigin);
	~Sprite();

	void setTexture(std::shared_ptr<Texture>);
	void setTexture(std::shared_ptr<SDL_::Image>);
	void clearTexture();
	std::shared_ptr<Texture> getTexture() const { return texture_; }

	void draw(std::shared_ptr<Shader>);

	const auto &getPos() const { return pos_; }
	const auto getXPos() const { return pos_.getX(); }
	const auto getYPos() const { return pos_.getY(); }
	const auto getZPos() const { return pos_.getZ(); }

	const auto &getSize() const { return size_; }
	const auto getWidth() const { return size_.getWidth(); }
	const auto getHeight() const { return size_.getHeight(); }

	const auto &getOffset() const { return offset_; }
	const auto getXOffset() const { return offset_.getX(); }
	const auto getYOffset() const { return offset_.getY(); }
	const auto getZOffset() const { return offset_.getZ(); }

	void setPos(const geo::Vector3f &pos) { pos_ = pos; }
	void setXPos(const float x) { pos_.setX(x); }
	void setYPos(const float y) { pos_.setY(y); }
	void setZPos(const float z) { pos_.setZ(z); }

	void setSize(const geo::Sizef &size) { size_ = size; }
	void setWidth(const float w) { size_.setWidth(w); }
	void setHeight(const float h) { size_.setHeight(h); }

	void setOffset(const geo::Vector3f &offset) { offset_ = offset; }
	void setXOffset(const float x) { offset_.setX(x); }
	void setYOffset(const float y) { offset_.setY(y); }
	void setZOffset(const float z) { offset_.setZ(z); }

	void setAlpha(uint8_t alpha) { alpha_ = alpha; }
	uint8_t getAlpha() const { return alpha_; }

	void setScale(double scale) { scale_ = scale; }
	double getScale() const { return scale_; }


private:
	static std::shared_ptr<VertexArray> createSpriteVerts(const XOrigin, const YOrigin, const std::array<float, 4> &);

	std::shared_ptr<Texture> texture_;
	std::shared_ptr<VertexArray> vertexArray_;
	geo::Vector3f pos_;
	geo::Vector3f offset_;
	geo::Sizef size_;
	uint8_t alpha_;
	float scale_;
	const XOrigin xorig_;
	const YOrigin yorig_;
};

} // GL_

#endif // GLSPRITE_H_
