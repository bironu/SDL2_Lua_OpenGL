#include "gl/widget/GLSprite.h"
#include "gl/GLTexture.h"
#include "gl/GLVertexArray.h"
#include "gl/GLShader.h"
#include "geo/Matrix.h"
#include "geo/Calculator.h"
#include "sdl/SDLImage.h"
#include <SDL2/SDL_opengl.h>

namespace GL_
{

Sprite::Sprite()
	: texture_()
	, vertexArray_()
	, alpha_(1.0f)
	, isChange_()
{
}

void Sprite::setTexture(std::shared_ptr<Texture> texture)
{
	texture_ = texture;
	vertexArray_.reset();
	if (texture) {
		setWidth(texture->getWidth() / 1080.0f);
		setHeight(texture->getHeight() / 1080.0f);
	}
}

void Sprite::setTexture(std::shared_ptr<SDL_::Image> surface)
{
	setTexture(std::make_shared<Texture>(surface));
}

void Sprite::clearTexture()
{
	texture_.reset();
	vertexArray_.reset();
	setWidth(0.0f);
	setHeight(0.0f);
}

void Sprite::draw(std::shared_ptr<Shader> shader)
{
	if (!texture_ || !shader) {
		return;
	}

	shader->setMatrixUniform("uWorldTransform", getMatrix());
	texture_->bind();
	getSpriteVerts()->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

std::shared_ptr<VertexArray> Sprite::getSpriteVerts()
{
	if (!vertexArray_) {
		const std::array<float, 4> &texRange = texture_->getTexRange();
		const float tleft = texRange[0];
		const float ttop = texRange[1];
		const float tright = texRange[2];
		const float tbottom = texRange[3];

		const float vleft = -0.5f;
		const float vright = 0.5f;
		const float vtop = 0.5f;
		const float vbottom = -0.5f;

		const float vertices[] = {
			vleft,  vtop, 0.f, tleft, ttop, // top left
			vright,  vtop, 0.f, tright, ttop, // top right
			vright, vbottom, 0.f, tright, tbottom, // bottom right
			vleft, vbottom, 0.f, tleft, tbottom  // bottom left
		};

		const unsigned int indices[] = {
			0, 3, 1,
			1, 3, 2
		};
		vertexArray_ = std::make_shared<VertexArray>(vertices, 4, indices, 6);
	}
	return vertexArray_;
}


} // GL_
