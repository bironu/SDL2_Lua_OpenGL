#ifndef GLSPRITE_H_
#define GLSPRITE_H_

#include "geo/AffineMap.h"
#include "gl/widget/GLWidget.h"
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
class Sprite : public Widget
{
public:
	UNCOPYABLE(Sprite);

	Sprite();
	virtual ~Sprite() override = default;

	void setTexture(std::shared_ptr<Texture>);
	void setTexture(std::shared_ptr<SDL_::Image>);
	void clearTexture();
	std::shared_ptr<Texture> getTexture() const { return texture_; }

	virtual void draw(std::shared_ptr<Shader>) override;

	void setAlpha(float alpha) { alpha_ = alpha; }
	float getAlpha() const { return alpha_; }

private:
	std::shared_ptr<VertexArray> getSpriteVerts();

	std::shared_ptr<Texture> texture_;
	std::shared_ptr<VertexArray> vertexArray_;
	geo::AffineMap affine_;
	geo::Matrix4x4f matrix_;
	float alpha_;
	bool isChange_;
};

} // GL_

#endif // GLSPRITE_H_
