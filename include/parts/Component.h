#pragma once
#if !defined(PARTS_COMPONENT_H_)
#define PARTS_COMPONENT_H_

#include "misc/Uncopyable.h"
#include <stdint>

namespace parts
{

class Parts;
class Component
{
public:
	Component(Parts &owner, int updateOrder = 100);
	virtual ~Component();
	virtual void update(uint32_t tick) = 0;
	int getUpdateOrder() const { return mUpdateOrder; }

private:
	// Owning actor
	Parts &owner_;
	// Update order of component
	const int order_;
};

}

#endif // PARTS_COMPONENT_H_
