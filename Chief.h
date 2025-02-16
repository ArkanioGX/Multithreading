#pragma once
#include "Actor.h"

class Chief : public Actor
{
public:
	Chief(Restaurant* inOwner);
	void LaunchBehavior() override;
};

