#include "Cooker.h"
#include "Restaurant.h"
#include <sstream>

Cooker::Cooker(Restaurant* inOwner):
	Actor(inOwner)
{
	currentJob = Data::Cooker;
}

void Cooker::LaunchBehavior()
{
	Actor::LaunchBehavior();
	while (isActive) {
		std::shared_ptr<Data::Ingredients> newOrd = Restaurant::Instance()->IngredientsToPrep.try_pop();
		if (newOrd != nullptr) {
			Data::Ingredients currentOrder = *newOrd;
			std::stringstream ss;
			ss << getName() << "cooking " << Data::getStringValue(currentOrder.toPrepare) << " for " << currentOrder.orderPointer->owner->getName() << "'s order \n";
			std::cout << ss.str();
			std::mutex m;
			std::condition_variable cv;
			auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(3000);
			std::unique_lock<std::mutex> lk(m);
			if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {
				
				ss.str("");
				ss << getName() << "finished cooking " << Data::getStringValue(currentOrder.toPrepare) << " for " << currentOrder.orderPointer->owner->getName() << "'s order \n";
				std::cout << ss.str();
				currentOrder.orderPointer->addIngredientCooked(currentOrder.toPrepare);
			}
		}
	}
}
