#include "Waiter.h"
#include "Restaurant.h"
#include <sstream>

Waiter::Waiter(Restaurant* inOwner):
	Actor(inOwner)
{
	currentJob = Data::Waiter;
}

void Waiter::LaunchBehavior()
{
	Actor::LaunchBehavior();

	while (isActive) {
		std::shared_ptr<Data::Order*> newOrd = Restaurant::Instance()->clientsWaiting.try_pop();
		if (newOrd != nullptr) {
			Data::Order* currentOrder = *newOrd;
			std::stringstream ss;
			ss << currentOrder->owner->getName() << "'s Order getting picked up by " << getName() << "\n";
			std::cout << ss.str();
			isServing = true;

			std::mutex m;
			std::condition_variable cv;
			auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(2000);
			std::unique_lock<std::mutex> lk(m);
			while (isServing) {
				if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {
					ss.str(std::string());
					ss << currentOrder->owner->getName() << "'s Order ready to be prepared ! ";
					ss << currentOrder->getOrderContentAsString() << std::endl;
					std::cout << ss.str();

					for (Data::Meals m : currentOrder->getOrderContent()) {
						Data::Ingredients ing;
						ing.orderPointer = currentOrder;
						ing.toPrepare = m;
						Restaurant::Instance()->IngredientsToPrep.push(ing);
						ss.str(std::string());
						ss << Data::getStringValue(m) << " from " << currentOrder->owner->getName()<< "sent to the kitchen !" << std::endl;
						std::cout << ss.str();
					}
					
					
					
					isServing = false;
				}
			}
		}
		newOrd = Restaurant::Instance()->MealPrepped.try_pop();
		if (newOrd != nullptr) {
			Data::Order* currentOrder = *newOrd;
			std::stringstream ss;
			ss << currentOrder->owner->getName() << "'s finished order getting picked up by " << getName() << "\n";
			std::cout << ss.str();
			isServing = true;

			std::mutex m;
			std::condition_variable cv;
			auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(2000);
			std::unique_lock<std::mutex> lk(m);
			while (isServing) {
				if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {
					ss.str(std::string());
					ss << currentOrder->owner->getName() << "'s finished order given | ";
					ss << currentOrder->getOrderContentAsString() << std::endl;
					currentOrder->isDelivered = true;
					dynamic_cast<Customer*>(currentOrder->owner)->DeliverOrder(currentOrder);
					std::cout << ss.str();
					isServing = false;
				}
			}
		}
	}
}
