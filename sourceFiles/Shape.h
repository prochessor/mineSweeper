#pragma once

#include "Block.h"
#include <time.h>

using namespace std;

class Shape {
public:

	int* x;
	int* y;
	int numberOfBlocks;
	int shapeNumber;
	int rotation;
	int v;
	int h = 1;
public:
	Shape();
	void giveShape();
	void giveShapeColor(Block blocks[][15],int,int,int);

};
