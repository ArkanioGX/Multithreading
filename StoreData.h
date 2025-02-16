#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include "Matrix.h"


void SequentialSumRef(std::vector<float> table, int begin, int end, float& result);
void SequentialSumPartMutex(std::vector<float> table, std::mutex& lock, float& result, int begin, int end);

float SequentialSum(std::vector<float> table, int begin = 0, int end = -1) {
	float result = 0;
	if (end == -1) end = table.size();
	for (int i = begin; i < end; i++) {
		result += table[i];
	}
	return result;
}

void SequentialSumRef(std::vector<float> table, int begin, int end, float& result) {
	result = SequentialSum(table, begin, end);
}

void DumbCountTo1000(bool isEven) {
	for (int i = isEven ? 0 : 1; i < 1000; i += 2) {
		std::string str = std::to_string(i) + ", ";
		std::cout << str;
	}
}

void ThreadSafeCountTo1000(std::mutex& mtx,int& currentNumber, bool isEven) {
	while (currentNumber < 1000) {
		if (isEven ^ (currentNumber % 2 == 1)) {
			mtx.lock();
			currentNumber++;
			std::cout << currentNumber << ", ";
			mtx.unlock();
		}
	}
}

float SequentialSumPart(std::vector<float> table, int parts) {
	float result = 0;

	std::vector<float> results;
	std::vector<std::thread*> threads;
	
	results.resize(parts);
	float partDivided = table.size() / parts;
	for (int i = 0; i < parts; i++) {

		std::thread* currentThread = new std::thread(SequentialSumRef,table,std::floor(partDivided*i), std::ceil(partDivided * (i+1)), std::ref(results[i]));
		threads.push_back(currentThread);
	}
	for (int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}
	for (int i = 0; i < results.size(); i++) {
		result += results[i];
	}
	return result;
}

void SequentialSumPartMutex(std::vector<float> table, std::mutex& lock, float& result, int begin = 0, int end = -1) {
	float r = 0;
	if (end == -1) end = table.size();
	for (int i = begin; i < end; i++) {
		r += table[i];
	}
	lock.lock();
	result += r;
	lock.unlock();
}

float SequentialSumGlobalMutex(std::vector<float> table, int parts) {
	float result = 0;

	std::vector<float> results;
	std::vector<std::thread*> threads;
	std::mutex lock;

	results.resize(parts);
	float partDivided = table.size() / parts;
	for (int i = 0; i < parts; i++) {

		std::thread* currentThread = new std::thread(SequentialSumPartMutex, table, std::ref(lock), std::ref(result), std::floor(partDivided * i), std::ceil(partDivided * (i + 1)));
		threads.push_back(currentThread);
	}
	for (int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}
	
	return result;
}


