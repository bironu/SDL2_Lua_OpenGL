// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Actor.h"

namespace Chapter05
{

class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();
	
	class CircleComponent* GetCircle() { return mCircle; }
private:
	class CircleComponent* mCircle;
};

}
