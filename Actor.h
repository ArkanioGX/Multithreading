#pragma once
#include "Datas.h"

class Actor
{
public:
	Actor(class Restaurant* inOwner);

	virtual void LaunchBehavior();

	void setID(int inID);
	void setActive(bool b);

	std::string getName();
protected:
	bool isActive = true;
	int ID = -1;
	Data::Job currentJob = Data::Job::Undefined;
};

