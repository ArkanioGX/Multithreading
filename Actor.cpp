#include "Actor.h"
#include "Restaurant.h"
#include <sstream>

Actor::Actor(Restaurant* inOwner)
{
	
}

void Actor::LaunchBehavior()
{
	std::stringstream ss;
	ss << getName() << "is Active ! \n";
	std::cout << ss.str();
}

void Actor::setID(int inID)
{
	ID = inID;
}

void Actor::setActive(bool b)
{
	isActive = b;
}

std::string Actor::getName()
{
	std::stringstream ss;
	ss << getStringValue(currentJob) << " " << ID << " ";
	return ss.str();
}
