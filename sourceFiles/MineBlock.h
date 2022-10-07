#pragma once
#include "Block.h"

class MineBlock :public Block
{
public:
	virtual void increaseN();
	MineBlock();
	void print();
	int getN();
};
