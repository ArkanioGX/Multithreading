#include "Chief.h"
#include "Restaurant.h"
#include <sstream>

Chief::Chief(Restaurant* inOwner):
	Actor(inOwner)
{
	currentJob = Data::Chief;
}

void Chief::LaunchBehavior()
{
	Actor::LaunchBehavior();
	while (isActive) {
		std::shared_ptr<Data::Order*> newOrd = Restaurant::Instance()->IngredientsPrepped.try_pop();
		if (newOrd != nullptr) {
			Data::Order* currentOrder = *newOrd;
			std::stringstream ss;
			ss << getName() << "finishing " << currentOrder->owner->getName() << " meal ! \n";
			std::cout << ss.str();
			std::mutex m;
			std::condition_variable cv;
			auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);
			std::unique_lock<std::mutex> lk(m);
			if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {

				ss.str("");
				ss << getName() << "finished cooking " << currentOrder->owner->getName() << "'s order  | " << currentOrder->getOrderContentAsString()<< "\n";
				currentOrder->isFinished = true;
				Restaurant::Instance()->MealPrepped.push(currentOrder);
				std::cout << ss.str();
			}
		}
	}
}
