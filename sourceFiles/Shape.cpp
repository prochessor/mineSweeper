#include "Shape.h"
#include "Board.h"
using namespace std;
int previousV = -1;
int previousS = -1;
Shape::Shape()
{
	x = y = nullptr;
	numberOfBlocks = 0;
	shapeNumber = 0;
}
void Shape::giveShapeColor(Block blocks[][15], int r, int g, int b)
{

	for (int i = 0; i < numberOfBlocks; ++i)
	{
		blocks[y[i]][x[i]].giveColor(r, g, b);
	}
}
void Shape::giveShape()
{
	srand(time(0));
	int shape = rand() % 6;
	while (shape == previousS)
	{
		shape = rand() % 6;
	}
	previousS = shape;
	rotation = rand() % 4 + 1;

	if (shape == 0)
	{
		v = rand() % 13 + 1;
		while (v == previousV)
		{
			v = rand() % 13 + 1;

		}
		previousV = v;
		numberOfBlocks = 4;
		shapeNumber = 0;
	}
	else if (shape == 1)
	{
		v = rand() % 13 + 1;
		while (v == previousV)
		{
			v = rand() % 13 + 1;

		}
		previousV = v;
		numberOfBlocks = 4;
		shapeNumber = 1;
	}
	else if (shape == 2)
	{
		v = rand() % 13 + 1;
		while (v == previousV)
		{
			v = rand() % 13 + 1;

		}
		previousV = v;
		numberOfBlocks = 4;
		shapeNumber = 2;

	}
	else if (shape == 3)
	{
		v = rand() % 12 + 1;
		while (v == previousV)
		{
			v = rand() % 12 + 1;

		}
		previousV = v;
		numberOfBlocks = 4;
		shapeNumber = 3;

	}
	else if (shape == 4)
	{
		v = rand() % 14 + 1;

		while (v == previousV)
		{
			v = rand() % 14 + 1;

		}
		previousV = v;


		numberOfBlocks = 3;
		shapeNumber = 4;
	}
	else if (shape == 5)
	{
		v = rand() % 14 + 1;

		while (v == previousV)
		{
			v = rand() % 14 + 1;

		}
		previousV = v;
		numberOfBlocks = 4;
		shapeNumber = 5;
	}
	srand(time(0));
	Board::controlShape(*this, shapeNumber, rotation);
}

