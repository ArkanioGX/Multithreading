#pragma once
#include "Actor.h"

class Customer : public Actor
{
public:
	Customer(Restaurant* inOwner);
	void LaunchBehavior() override;
	void DeliverOrder(Data::Order*);

private:
	Data::Order* orderEating;
};

