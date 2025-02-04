#include <iostream>
#include <thread>
#include "Matrix.h"
#include "StoreData.h"

using std::cout;
using std::endl;

void sayHello() {

	cout << "Hello world \n";

}

int main() {

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

	mat1 = Matrix({
		{1	,2,	3},
		{4,	5,	6} });
	mat2 = Matrix({
		{7,	8},
		{9,	10},
		{11,12} });
	Matrix matMult2 = mat1 * mat2;

	//#2 - Mutex
	std::vector<float> list = { 1,5,7,6,1,95,25,147,56,133,42,17,99,60,34,6 };
	float sumSqt = SequentialSum(list);
	float sumSqtPart = SequentialSumPart(list,4);
	return 0;

}