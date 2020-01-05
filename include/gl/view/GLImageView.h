#if !defined(GLIMAGEVIEW_H_)
#define GLIMAGEVIEW_H_

#include "GLView.h"
#include "GLViewOrigin.h"

namespace SDL_
{
class Image;
}

namespace GL_
{

class Sprite;
class Texture;
class VertexArray;
class ImageView: public View
{
public:
	ImageView(XOrigin &xorigin = xcenter, YOrigin &yorigin = ycenter);
	virtual ~ImageView() override = default;

	virtual void draw(std::shared_ptr<Shader> shader) override;

	void setImage(std::shared_ptr<SDL_::Image> image);
	void setImage(std::shared_ptr<Texture> texture);
	std::shared_ptr<Texture> getImage() const { return texture_; }

	void setWrapContentSize();

private:
	std::shared_ptr<VertexArray> getSpriteVerts();

	std::shared_ptr<Texture> texture_;
	std::shared_ptr<VertexArray> vertexArray_;
};

} // GL_

#endif // GLIMAGEVIEW_H_
