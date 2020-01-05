#ifndef WIDGET_ROTATEMENU_H_
#define WIDGET_ROTATEMENU_H_

#include "misc/Uncopyable.h"
#include "gl/widget/GLSprite.h"
#include <memory>
#include <vector>

namespace GL_ {

template<typename T>
class RotateMenu
{
public:
	UNCOPYABLE(RotateMenu);
	RotateMenu()
		: listMenuItem_()
		, radius_()
		, degrees_()
	{

	}
	virtual ~RotateMenu(){}

	void setRadius(float radius) { radius_ = radius; }
	float getRadius() const { return radius_; }

	void setDegrees(float degrees)
	{
		while(true) {
			if (degrees < 0.0f) {
				degrees += MAX_DEGREES;
			}
			else if (MAX_DEGREES <= degrees) {
				degrees -= MAX_DEGREES;
			}
			else {
				break;
			}
		}
		degrees_ = degrees;
	}
	float getDegrees() const { return degrees_; }

	float computeDgrees(int oldPos, int movePos, uint32_t duration)
	{
		if (movePos == 0) {
			return 0.0f;
		}

		const int newPos = oldPos + movePos;
		const float delta = (MAX_DEGREES / listMenuItem_.size());
		float endDegrees = delta * newPos;

		const float beginDegrees = delta * oldPos;
		const float currDegrees = getDegrees();

		if (currDegrees != beginDegrees) {
			return 0.0f;
		}

		float subDegrees;
		// 左
		if (movePos < 0) {
			if (currDegrees < endDegrees) {
				endDegrees -= MAX_DEGREES;
			}
//			if (beginDegrees < currDegrees) {
//				return {endDegrees, 0};
//			}
			subDegrees = currDegrees - endDegrees;
		}
		// 右
		else {
			if (endDegrees < currDegrees) {
				endDegrees += MAX_DEGREES;
			}
			// current = c, begin = b, end = e とした場合
			// c = b < e 停止したカーソルを右に移動しようとした時
			// c < b < e 右に移動中のカーソルを右に移動しようとした時
			// b < c < e 左に移動中のカーソルを右に移動しようとした時
			subDegrees = endDegrees - currDegrees;
		}

		return endDegrees;
	}

	void addMenuItem(std::shared_ptr<Sprite> item) { listMenuItem_.push_back(item); }
	void clearMenuItem() { listMenuItem_.clear(); }
	const std::vector<std::shared_ptr<T>> &getMenuItemList() const { return listMenuItem_; }
	const auto getMenuItemListSize() const { return listMenuItem_.size(); }

	std::shared_ptr<T> getMenuItem(int index) {
//		const auto size = listMenuItem_.size();
//		if (index < 0) {
//			index += size;
//		}
//		else if (size <= index){
//			index -= size;
//		}
		return listMenuItem_[index];
	}

	virtual void draw() = 0;

	static constexpr double MAX_DEGREES = 360.0;

private:

	std::vector<std::shared_ptr<T>> listMenuItem_;
	double radius_;
	double degrees_;
};

} // namespace GL_

#endif // WIDGET_ROTATEMENU_H_
