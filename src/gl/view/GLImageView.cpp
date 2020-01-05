#include "gl/view/GLImageView.h"
#include "gl/GLTexture.h"
#include "gl/GLShader.h"
#include "gl/GLVertexArray.h"
#include "sdl/SDLImage.h"

namespace GL_
{

ImageView::ImageView(XOrigin &xorigin, YOrigin &yorigin)
	: View(xorigin, yorigin)
	, texture_()
	, vertexArray_()
{
}

void ImageView::setImage(std::shared_ptr<SDL_::Image> image)
{
	texture_ = std::make_shared<Texture>(image);
	setWrapContentSize();
	vertexArray_.reset();
}

void ImageView::setImage(std::shared_ptr<Texture> texture)
{
	texture_ = texture;
	setWrapContentSize();
	vertexArray_.reset();
}

void ImageView::draw(std::shared_ptr<Shader> shader)
{
	if (!texture_ || !shader) {
		return;
	}

	auto scale = geo::createScale(getWidth(), getHeight(), 1.0f);
	shader->setMatrixUniform("uWorldTransform", getMatrix() * scale);
	texture_->bind();
	getSpriteVerts()->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ImageView::setWrapContentSize()
{
	if(texture_){
		const double sw = texture_->getWidth();
		const double sh = texture_->getHeight();
		setWidth(sw);
		setHeight(sh);
	}
}

std::shared_ptr<VertexArray> ImageView::getSpriteVerts()
{
	if (!vertexArray_) {
		const std::array<float, 4> &texRange = texture_->getTexRange();
		const float tleft = texRange[0];
		const float ttop = texRange[1];
		const float tright = texRange[2];
		const float tbottom = texRange[3];

		const float vleft = getXOrigin().getLeft();
		const float vright = getXOrigin().getRight();
		const float vtop = getYOrigin().getTop();
		const float vbottom = getYOrigin().getBottom();

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

