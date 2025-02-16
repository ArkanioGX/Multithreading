#include <iostream>
#include <thread>
#include "Matrix.h"
#include "StoreData.h"
#include "Restaurant.h"

using std::cout;
using std::cin;
using std::endl;

void sayHello() {

	cout << "Hello world \n";

}

int main() {

	cout << "Matrix Multiplication \n";
	cout << "=============================\n";
	cout << "| 12  8  4 |     |  5 19  3 | \n";
	cout << "|  3 17 14 |  *  |  6 15  9 | \n";
	cout << "|  9  8 10 |     |  7  8 16 | \n";
	cout << "=============================\n";
	//#1 - Matrix Multiplication
	Matrix mat1 = Matrix({
		{12,8,	4},
		{3,	17,	14},
		{9,	8,	10} });
	Matrix mat2 = Matrix({
		{5,	19,	3},
		{6,	15,	9},
		{7,	8,	16} });
	Matrix matMult = mat1 * mat2;
	cout << "===========================\n";
	cout << "|  1  2  3 |     |  7  8 | \n";
	cout << "|  4  5  6 |  *  |  9 10 | \n";
	cout << "                 | 11 12 | \n";
	cout << "===========================\n";
	mat1 = Matrix({
		{1	,2,	3},
		{4,	5,	6} });
	mat2 = Matrix({
		{7,	8},
		{9,	10},
		{11,12} });
	Matrix matMult2 = mat1 * mat2;

	//#2 - Mutex
	//#2-1 Sum of a table
	std::vector<float> list = { 1,5,7,6,1,95,25,147,56,133,42,17,99,60,34,6 };
	float sumSqt = SequentialSum(list);
	float sumSqtPart = SequentialSumPart(list,4);
	float sumSqtMutex = SequentialSumGlobalMutex(list, 4);

	//#2-2 Ordering
	cout << "\n";
	std::thread* t1 = new std::thread(DumbCountTo1000, false);
	std::thread* t2 = new std::thread(DumbCountTo1000, true);

	t1->join();
	t2->join();

	delete t1;
	delete t2;

	std::mutex lock;
	int count = 0;

	cout << "\n";
	t1 = new std::thread(ThreadSafeCountTo1000,std::ref(lock), std::ref(count), false);
	t2 = new std::thread(ThreadSafeCountTo1000, std::ref(lock), std::ref(count), true);

	t1->join();
	t2->join();

	//#3 Restaurant
	cout << "\n";
	Restaurant* FastFood = new Restaurant();
	FastFood->Launch();

	return 0;

}