#ifndef WIDGET_VERTICALROTATEMENU_H_
#define WIDGET_VERTICALROTATEMENU_H_

#include <memory>
#include <vector>

namespace GL_ {

class Shader;
class Sprite;
class VerticalRotateMenu
{
public:
	VerticalRotateMenu()
		: listMenuItem_()
		, radius_()
		, degrees_()
		, step_(3)
	{
	}
	~VerticalRotateMenu() = default;

	void setRadius(float radius) { radius_ = radius; }
	float getRadius() const { return radius_; }
	void setDegrees(float degrees);
	float getDegrees() const { return degrees_; }
	void addMenuItem(std::shared_ptr<Sprite> item) { listMenuItem_.push_back(item); }
	void clearMenuItem() { listMenuItem_.clear(); }
	const std::vector<std::shared_ptr<Sprite>> &getMenuItemList() const { return listMenuItem_; }
	const auto getMenuItemListSize() const { return listMenuItem_.size(); }
	std::shared_ptr<Sprite> getMenuItem(int index);
	void prepare();

	void draw(std::shared_ptr<Shader> shader);

	static constexpr double MAX_DEGREES = 360.0;

private:
	std::vector<std::shared_ptr<Sprite>> listMenuItem_;
	float radius_;
	float degrees_;
	const int step_;
};

} // namespace GL_

#endif // WIDGET_VERTICALROTATEMENU_H_
