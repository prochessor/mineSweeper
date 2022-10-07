#pragma once
#include <iostream>
#include <string.h>
class Block
{
public:
	int x, y, z;
public:
	bool isFlaged, isExposed,isDark;
	std::string type;
	virtual int getN() = 0;
	virtual void increaseN() = 0;
	virtual void print();
	void setAttributes(int x, int y, int z,int h);
	bool compareValues(int,int);
	void toggleFlagValue(int&);
};
