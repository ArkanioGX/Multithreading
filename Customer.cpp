#include "Customer.h"
#include "Restaurant.h"
#include <sstream>

Customer::Customer(Restaurant* inOwner):
	Actor(inOwner)
{
	currentJob = Data::Customer;
}

void Customer::LaunchBehavior()
{
	Actor::LaunchBehavior();

    std::mutex m;
    std::condition_variable cv;
    bool done = false;
    auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(5000);
    std::unique_lock<std::mutex> lk(m);
    while (!done) {
        if (cv.wait_until(lk, timeout) == std::cv_status::timeout) {
            Data::Order* ownOrder = new Data::Order(static_cast<Data::Meals>(rand() * (ID + 1) % Data::Meals::Lemonade) , static_cast<Data::Meals>(rand()*(ID+1) % Data::Meals::Lemonade), static_cast<Data::Meals>(rand() * (ID + 1) % Data::Meals::Lemonade), this);
            done = true;
        }     
    }
    while (orderEating == nullptr) {
        //Yeah its really unoptimized 
    }
    std::stringstream ss;
    ss << getName()<< "is eating his order | " << orderEating->getOrderContentAsString() << "\n";
    std::cout << ss.str();
    auto const timeout2 = std::chrono::steady_clock::now() + std::chrono::milliseconds(5000);
    done = false;
    while (!done) {
        if (cv.wait_until(lk, timeout2) == std::cv_status::timeout) {
            done = true;
        }
    }
    
    ss.str("");
    ss << getName() << "finished eating his order | " << orderEating->getOrderContentAsString() << "\n";
    std::cout << ss.str();

    Restaurant::Instance()->RemoveClient(this);
}

void Customer::DeliverOrder(Data::Order* ord)
{
    orderEating = ord;
}
