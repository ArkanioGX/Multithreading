#pragma once
#include "Actor.h"

class Waiter : public Actor
{
private:
	bool isServing = false;
public:
	Waiter(Restaurant* inOwner);
	void LaunchBehavior() override;
};

