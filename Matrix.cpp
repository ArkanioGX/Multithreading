#include "Matrix.h"

void Matrix::computeSize()
{
	Size2D newSize;
	newSize.x = value.size();
	newSize.y = value[0].size();
	size = newSize;
}
