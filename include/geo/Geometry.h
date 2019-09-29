#if !defined(GEOMETRY_H_)
#define GEOMETRY_H_

#include "geo/Vector2.h"
#include <SDL2/SDL_rect.h>

class RectTest;

class Point final : public SDL_Point
{
public:
	Point(decltype(x) x_pos, decltype(y) y_pos)
		: SDL_Point{x_pos, y_pos}
	{
	}
	Point()
		: Point(0, 0)
	{
	}
	~Point() = default;
	decltype(x) get_x_pos() const { return x;}
	decltype(y) get_y_pos() const { return y;}
	void set_x_pos(decltype(x) x_pos){ x = x_pos;}
	void set_y_pos(decltype(y) y_pos){ y = y_pos;}
	void set_point(decltype(x) x_pos, decltype(y) y_pos)
	{
		set_x_pos(x_pos);
		set_y_pos(y_pos);
	}

	const Point &operator+=(const Point &pos)
	{
		set_x_pos(get_x_pos()+pos.get_x_pos());
		set_y_pos(get_y_pos()+pos.get_y_pos());
		return *this;
	}
};

inline const Point operator+(const Point &l, const Point &r)
{
	return {l.get_x_pos()+r.get_x_pos(), l.get_y_pos()+r.get_y_pos()};
}

//=============================================================================
//
class Rect final : public SDL_Rect
{
	friend class RectTest;
public:
	Rect()
		: SDL_Rect{0, 0, 0, 0}
	{
	}
	Rect(decltype(x) x_pos, decltype(y) y_pos, decltype(w) width, decltype(h) height)
		: SDL_Rect{x_pos, y_pos, width, height}
	{
	}
	Rect(const Point &point, const geo::Sizei &size)
		: SDL_Rect{point.get_x_pos(), point.get_y_pos(), size.getWidth(), size.getHeight()}
	{
	}
	~Rect() = default;

	decltype(x) getXPos() const { return x;}
	decltype(y) getYPos() const { return y;}
	decltype(w) getWidth() const { return w;}
	decltype(h) getHeight() const { return h;}

	const geo::Sizei getSize() const { return {getWidth(), getHeight()}; }
	const Point getPos() const { return {getXPos(), getYPos()}; }

	bool isEmpty() const { return ::SDL_RectEmpty(this);}
	bool is_point_in_rect(decltype(x) x_pos, decltype(y) y_pos) const
	{
		return ((getXPos() <= x_pos) && (x_pos < (getXPos() + getWidth())) && (getYPos() <= y_pos) && (y_pos < (getYPos() + getHeight())));
	}

	bool is_point_in_rect(const Point &point) const
	{
		return is_point_in_rect(point.get_x_pos(), point.get_y_pos());
	}

	void setXPos(decltype(x) x_pos){ x = x_pos;}
	void setYPos(decltype(y) y_pos){ y = y_pos;}
	void setWidth(decltype(w) width){ w = width;}
	void setHeight(decltype(h) height){ h = height;}
	void setRect(decltype(x) x_pos, decltype(y) y_pos, decltype(w) width, decltype(h) height)
	{
		setXPos(x_pos);
		setYPos(y_pos);
		setWidth(width);
		setHeight(height);
	}
	void setRectEmpty(){ setRect(0, 0, 0, 0);}

	void offsetRect(decltype(x) add_x, decltype(y) add_y)
	{
		setXPos(getXPos() + add_x);
		setYPos(getYPos() + add_y);
	}

	void operator=(const Rect &rect){ setRect(rect.x, rect.y, rect.w, rect.h);}
	bool operator==(const Rect &rect) const
	{
		return ::SDL_RectEquals(this, &rect);
	}
	bool operator!=(const Rect &rect) const { return !(*this == rect);}

	const Rect operator&(const Rect &rect) const
	{
		Rect result;
		if(!::SDL_IntersectRect(this, &rect, &result)){
			result.setRectEmpty();
		}
		return result;
	}
	const Rect operator|(const Rect &rect) const
	{
		Rect result;
		::SDL_UnionRect(this, &rect, &result);
		return result;
	}
	bool operator&&(const Rect &rect) const
	{
		return ::SDL_HasIntersection(this, &rect);
	}
};

#endif // GEOMETRY_H_
