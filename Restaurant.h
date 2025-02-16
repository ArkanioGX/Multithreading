#pragma once
#include <iostream>
#include "Cooker.h"
#include "Chief.h"
#include "Waiter.h"
#include "Customer.h"
#include <thread>
#include <vector>

class Restaurant
{
public:
	Restaurant();
	void Launch();

	static Restaurant* Instance() {
		if (instance != nullptr) {return instance;}
		else {return new Restaurant();}
	}

	ThreadsafeQueue<Data::Order*> clientsWaiting;
	ThreadsafeQueue<Data::Ingredients> IngredientsToPrep;
	ThreadsafeQueue<Data::Order*> IngredientsPrepped;
	ThreadsafeQueue<Data::Order*> MealPrepped;

	void RemoveClient(Customer*);

private:
	static Restaurant* instance;

	const int CustomersNumber = 8;
	const int CookNumber = 3;
	const int ChiefNumber = 1;
	const int WaiterNumber = 2;

	std::vector<std::thread*> threads;
	std::vector<Customer*> customers;
	std::vector<Cooker*> cookers;
	std::vector<Chief*> chiefs;
	std::vector<Waiter*> waiters;
};

