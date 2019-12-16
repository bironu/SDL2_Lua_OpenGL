// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

namespace chapter05
{

class Asteroid : public Actor
{
public:
	Asteroid(Chapter05Scene* game);
	~Asteroid();
	
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};

}
