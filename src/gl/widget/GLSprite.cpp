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

Sprite::Sprite(XOrigin xorigin, YOrigin yorigin)
	: texture_()
	, vertexArray_()
	, size_(0.0f, 0.0f)
	, alpha_(1.0f)
	, xorigin_(xorigin)
	, yorigin_(yorigin)
	, isChange_()
{
}

Sprite::~Sprite()
{
}

void Sprite::setTexture(std::shared_ptr<Texture> texture)
{
	texture_ = texture;
	vertexArray_.reset();
	if (texture) {
		setWidth(texture->getWidth());
		setHeight(texture->getHeight());
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

const geo::Matrix4x4f &Sprite::getMatrix()
{
	if (isChange() || isChange_) {
		matrix_ = affine_.getMatrix() * geo::createScale(getWidth(), getHeight(), 1.0f);
		isChange_ = false;
	}
	return matrix_;
}

std::shared_ptr<VertexArray> Sprite::getSpriteVerts()
{
	if (!vertexArray_) {
		const std::array<float, 4> &texRange = texture_->getTexRange();
		const float tleft = texRange[0];
		const float ttop = texRange[1];
		const float tright = texRange[2];
		const float tbottom = texRange[3];

		float vtop, vbottom, vleft, vright;
		switch(xorigin_)
		{
		case XOrigin::Left:
			vleft = 0.0f;
			vright = 1.0f;
			break;
		case XOrigin::Right:
			vleft = -1.0f;
			vright = 0.0f;
			break;
		case XOrigin::Center:
		default:
			vleft = -0.5f;
			vright = 0.5f;
			break;
		}

		switch(yorigin_)
		{
		case YOrigin::Top:
			vtop = 0.0f;
			vbottom = -1.0f;
			break;
		case YOrigin::Bottom:
			vtop = 1.0f;
			vbottom = 0.0f;
			break;
		default:
		case YOrigin::Center:
			vtop = 0.5f;
			vbottom = -0.5f;
			break;
		}

		const float vertices[] = {
			vleft,  vtop, 0.f, tleft, ttop, // top left
			vright,  vtop, 0.f, tright, ttop, // top right
			vright, vbottom, 0.f, tright, tbottom, // bottom right
			vleft, vbottom, 0.f, tleft, tbottom  // bottom left
		};

		const unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		vertexArray_ = std::make_shared<VertexArray>(vertices, 4, indices, 6);
	}
	return vertexArray_;
}


} // GL_
