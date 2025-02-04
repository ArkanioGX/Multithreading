#pragma once
#include <vector>
#include <thread>
#include "Matrix.h"

float SequentialSum(std::vector<float> table, int begin = 0, int end = -1) {
	float result = 0;
	if (end == -1) end = table.size();
	for (int i = begin; i < end; i++) {
		result += table[i];
	}
	return result;
}

float SequentialSumPart(std::vector<float> table, int parts) {
	float result = 0;

	std::vector<float> results;
	std::vector<std::thread> threads;
	
	for (int i = 0; i < parts; i++) {
		std::thread currentThread = std::thread(SequentialSum,table,0,1,std::ref(result[i]));
		threads.push_back(currentThread);
	}
	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}
	for (int i = 0; i < results.size(); i++) {
		result += results[i];
	}
	return result;
}
