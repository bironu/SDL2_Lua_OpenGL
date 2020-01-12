#ifndef WIDGET_VERTICALROTATEMENU_H_
#define WIDGET_VERTICALROTATEMENU_H_

#include "gl/widget/GLWidgetGroup.h"
#include <memory>
#include <vector>

namespace GL_ {

class Shader;
class Sprite;
class VerticalRotateMenu : public WidgetGroup
{
public:
	VerticalRotateMenu()
		: listMenuItem_()
		, radius_()
		, degrees_()
		, step_(3)
	{
	}
	virtual ~VerticalRotateMenu() override = default;

	void setRadius(float radius) { radius_ = radius; }
	float getRadius() const { return radius_; }
	void setDegrees(float degrees);
	float getDegrees() const { return degrees_; }
	void prepare();

	//virtual void draw(std::shared_ptr<Shader> shader) override;

	static constexpr double MAX_DEGREES = 360.0;

private:
	std::vector<std::shared_ptr<Sprite>> listMenuItem_;
	float radius_;
	float degrees_;
	const int step_;
};

} // namespace GL_

#endif // WIDGET_VERTICALROTATEMENU_H_
