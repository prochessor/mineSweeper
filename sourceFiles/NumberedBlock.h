#pragma once
#include "Block.h"
#include "Board.h"
class NumberedBlock :public Block
{
public:
	int n=0;
	void increaseN();
	NumberedBlock();
	void print();
	int getN();
};

