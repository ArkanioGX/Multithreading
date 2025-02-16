#include "Restaurant.h"

Restaurant* Restaurant::instance = nullptr;

Restaurant::Restaurant()
{
	if (instance != nullptr) {
		delete this;
	}
	instance = this;
}

void Restaurant::Launch()
{
	//Customer Setup
	for (int i = 0; i < CustomersNumber; i++) {
		Customer* c = new Customer(this);
		c->setID(i);
		customers.push_back(c);
		threads.push_back(new std::thread([c]() { c->LaunchBehavior(); }));
	}
	for (int i = 0; i < CookNumber; i++) {
		Cooker* c = new Cooker(this);
		c->setID(i);
		cookers.push_back(c);
		threads.push_back(new std::thread([c]() { c->LaunchBehavior(); }));
	}
	for (int i = 0; i < ChiefNumber; i++) {
		Chief* c = new Chief(this);
		c->setID(i);
		chiefs.push_back(c);
		threads.push_back(new std::thread([c]() { c->LaunchBehavior(); }));
	}
	for (int i = 0; i < WaiterNumber; i++) {
		Waiter* c = new Waiter(this);
		c->setID(i);
		waiters.push_back(c);
		threads.push_back(new std::thread([c]() { c->LaunchBehavior(); }));
	}
	for (std::thread* t : threads) {
		t->join();
	}
}

void Restaurant::RemoveClient(Customer* c)
{
	customers.erase(std::find(customers.begin(), customers.end(), c));
	delete c;
	
	if (customers.empty()) {
		std::cout << "Restaurant closing !! ";
		for (auto a : waiters) {
			a->setActive(false);
		}
		for (auto a : cookers) {
			a->setActive(false);
		}
		for (auto a : chiefs) {
			a->setActive(false);
		}
	}
}
