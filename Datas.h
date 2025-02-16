#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>

class Actor;

namespace Data {


	enum Meals
	{
		Fries,
		Wedges,
		HashBrowns,
		Burger,
		CheeseBurger,
		Cake,
		IceCream,
		Water,
		Soda,
		Lemonade
	};
	std::string getStringValue(Meals m);

	enum Job {
		Undefined,
		Customer,
		Waiter,
		Chief,
		Cooker
	};
	std::string getStringValue(Job j);



	inline std::string getStringValue(Meals m) {
		switch (m) {
		case Fries:
			return "Fries";
		case Wedges:
			return "Wedges";
		case HashBrowns:
			return "HashBrowns";
		case Burger:
			return "Burger";
		case CheeseBurger:
			return "CheeseBurger";
		case Cake:
			return "Cake";
		case IceCream:
			return "IceCream";
		case Water:
			return "Water";
		case Soda:
			return "Soda";
		case Lemonade:
			return "Lemonade";
		}
	}

	inline std::string getStringValue(Job j)
	{
		switch (j) {
		case Chief:
			return "Chief";
		case Cooker:
			return "Cooker";
		case Waiter:
			return "Waiter";
		case Customer:
			return "Customer";
		default:
			return "Undefined Actor";
		}
	}

	

	struct Order {
	private:
		mutable std::mutex mut;
		std::condition_variable dataCond;

	public:
		Order(Meals m1, Meals m2, Meals m3, Actor* inOwner);
		void addIngredientCooked(Meals toAdd);

	private:
		std::vector<Meals> ingredientsToCook;
		std::vector<Meals> ingredientCooked;
	public:
		bool isFinished = false;
		bool isDelivered = false;

		Actor* owner;
		std::string getOrderContentAsString();
		std::vector<Meals> getOrderContent() {
			return ingredientsToCook;
		}
	};

	struct Ingredients {
		Meals toPrepare;
		Order* orderPointer;
	};
}



template<typename T>
class ThreadsafeQueue {
private:
    mutable std::mutex mut;
    std::queue<T> dataQueue;
    std::condition_variable dataCond;
public:
    ThreadsafeQueue() {};
    ThreadsafeQueue(const ThreadsafeQueue& other) {
        std::lock_guard<std::mutex> lk(other.mut);
        dataQueue = other.dataQueue;
    }
    ThreadsafeQueue& operator=(const ThreadsafeQueue&) = delete;
    void push(T newValue) {
        std::lock_guard<std::mutex> lk(mut);
        dataQueue.push(newValue);
        dataCond.notify_one();
    }

    void waitAndPop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this] {return !dataQueue.empty(); });
        value = dataQueue.front();
        dataQueue.pop();
    }
    std::shared_ptr<T> waitAndPop() {
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this] {return !dataQueue.empty(); });
        std::shared_ptr<T> res(std::make_shared<T>(dataQueue.front()));
        dataQueue.pop();
        return res;
    }
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.empty())
            return false;
        value = dataQueue.front();
        dataQueue.pop();
        return true;
    }
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(dataQueue.front()));
        dataQueue.pop();
        return res;
    }
    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return dataQueue.empty();
    }
};


