#include "Datas.h"
#include "Actor.h"
#include <sstream>
#include "Restaurant.h"

namespace Data {

	Order::Order(Meals m1, Meals m2, Meals m3, Actor* inOwner) :
		owner(inOwner)
	{
		ingredientsToCook = { m1,m2,m3 };
		std::stringstream ss;
		ss << owner->getName() << " is Ready to order \n";
		std::cout << ss.str();
		Restaurant::Instance()->clientsWaiting.push(this);
	}
	void Order::addIngredientCooked(Meals toAdd)
	{
		std::lock_guard<std::mutex> lk(mut);
		ingredientCooked.push_back(toAdd);
		dataCond.notify_one();
		if (ingredientCooked.size() == ingredientsToCook.size()) {
			std::stringstream ss;
			ss << "Ingredient of the order from " << owner->getName() << " are prepared and waiting for the chef to finish \n";
			Restaurant::Instance()->IngredientsPrepped.push(this);
			std::cout << ss.str();
		}
	}
	std::string Order::getOrderContentAsString()
	{
		std::stringstream ss;
		ss << "Order Content{ ";
		if (!ingredientsToCook.empty()) {
			for (int i = 0; i < ingredientsToCook.size(); i++) {
				ss << getStringValue(ingredientsToCook[i]);
				if (i != ingredientsToCook.size()-1) {
					ss << ", ";
				}
				else {
					ss << "} ";
				}
			}
		}
		else {
			for (int i = 0; i < ingredientCooked.size(); i++) {
				ss << getStringValue(ingredientCooked[i]);
				if (i != ingredientCooked.size()) {
					ss << ", ";
				}
			}
		}
		return ss.str();
	}
}