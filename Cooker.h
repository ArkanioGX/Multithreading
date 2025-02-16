#pragma once
#include "Actor.h"

class Cooker : public Actor
{
public:
	Cooker(Restaurant* inOwner);
	void LaunchBehavior() override;
};

