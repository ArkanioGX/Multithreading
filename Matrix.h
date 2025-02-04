#pragma once
#include <vector>
#include <thread>
#include <iostream>

struct Size2D {
	int x;
	int y;
};

class Matrix
{
public:

	Size2D GetSize() { return size; }

	void computeSize();

	Matrix()
	{
		value = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1} };

		computeSize();
	}

	explicit Matrix(std::vector<std::vector<float>> inMat)
	{
		value.insert(value.end(), inMat.begin(), inMat.end());
		computeSize();
	}

	friend Matrix operator*(const Matrix& a, const Matrix& b)
	{
		std::vector<std::vector<float>> newMatrix;
		std::vector<std::thread*> threads;
		
		if (a.size.x == b.size.x && a.size.y == b.size.y || a.size.x == b.size.y && a.size.y == b.size.x) {
			const int newSize = fmin(a.size.x, a.size.y);
			newMatrix.resize(newSize, std::vector<float>(newSize));
			
			for (int x = 0; x < newSize; x++) {
				for (int y = 0; y < newSize; y++) {
					std::thread* currentThread = new std::thread( Matrix::GetMultipliedMatrixValue, std::ref(a), std::ref(b), x, y, std::ref(newMatrix[x][y]));
					threads.push_back(currentThread);
				}
			}

			
		}
		else {
			std::cerr << "Matrice Multiplication not found";
			return Matrix();
		}

		for (int i = 0; i < threads.size(); i++) {
			threads[i]->join();
		}

		return Matrix(newMatrix);
	}

	Matrix& operator*=(const Matrix& right)
	{
		*this = *this * right;
		return *this;
	}

	static float GetMultipliedMatrixValue(const Matrix& a, const Matrix& b, int xPos, int yPos, float &Value)
	{
		float result = 0;
		int maxSize = fmax(a.size.x, a.size.y);
		for (int i = 0; i < maxSize; i++) {
			result += a.value[xPos][i] * b.value[i][yPos];
			std::cout << std::this_thread::get_id() << " : " << a.value[xPos][i] << " * " << b.value[i][yPos] << std::endl;
		}
		Value = result;
		return result;
	}

	

private:
	std::vector<std::vector<float>> value;
	Size2D size;

};

