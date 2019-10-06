#include "gl/GLSprite.h"
#include "gl/GLTexture.h"
#include "gl/GLVertexArray.h"
#include "gl/GLShader.h"
#include "geo/Matrix.h"
#include "geo/Calculator.h"
#include "sdl/SDLImage.h"
#include <SDL2/SDL_opengl.h>

namespace GL_
{

Sprite::Sprite(std::shared_ptr<Texture> texture, XOrigin xorigin, YOrigin yorigin)
	: texture_(texture)
	, vertexArray_(createSpriteVerts(xorigin, yorigin, texture->getTexRange()))
	, pos_()
	, offset_()
	, size_()
	, alpha_(255)
	, scale_(1.0)
	, xorig_(xorigin)
	, yorig_(yorigin)
{

}

Sprite::Sprite(std::shared_ptr<SDL_::Image> image, XOrigin xorigin, YOrigin yorigin)
	: Sprite(std::make_shared<Texture>(image), xorigin, yorigin)
{
}

Sprite::~Sprite()
{
}

void Sprite::setTexture(std::shared_ptr<Texture> texture)
{
	texture_ = texture;
	vertexArray_ = createSpriteVerts(xorig_, yorig_, texture->getTexRange());
}

void Sprite::setTexture(std::shared_ptr<SDL_::Image> surface)
{
	setTexture(std::make_shared<Texture>(surface));
}

void Sprite::clearTexture()
{
	texture_.reset();
}

void Sprite::draw(std::shared_ptr<Shader> shader)
{
	if (!texture_) {
		return;
	}

	// const auto alpha = getAlpha();
	// const GLubyte colors[] = {
	// 	255, 255, 255, alpha,
	// 	255, 255, 255, alpha,
	// 	255, 255, 255, alpha,
	// 	255, 255, 255, alpha,
	// };

	const geo::Matrix4x4f scale = geo::createScale<float>(
		getScale() * static_cast<float>(texture_->getWidth()),
		getScale() * static_cast<float>(texture_->getHeight()),
		1.0f);
	
	//const Matrix4x4f rotation = geo::createRotationZ<float>(getRotation());
	const geo::Matrix4x4f translation = geo::createTranslation<float>(getPos());
	const geo::Matrix4x4f world = translation * /*rotation * */ scale;
	
	shader->setMatrixUniform("uWorldTransform", world);
	texture_->bind();
	vertexArray_->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

std::shared_ptr<VertexArray> Sprite::createSpriteVerts(const XOrigin xorigin, const YOrigin yorigin, const std::array<float, 4> &texRange)
{
	float vtop, vbottom, vleft, vright;
	const float tleft = texRange[0];
	const float ttop = texRange[1];
	const float tright = texRange[2];
	const float tbottom = texRange[3];

	switch(xorigin)
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

	switch(yorigin)
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

	return std::make_shared<VertexArray>(vertices, 4, indices, 6);
}


} // GL_
