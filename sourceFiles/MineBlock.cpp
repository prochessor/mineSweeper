#include "MineBlock.h"
#include "help.h"
MineBlock::MineBlock()
{
	type = "MineBlock";
}
void MineBlock::increaseN(){}
void MineBlock::print()
{
	if (isExposed)
	{
		if (isDark)
		{
			myRects(x, y, x + 45, y + 45, 229, 194, 159);
		}
		else
		{
			myRects(x, y, x + 45, y + 45, 215, 184, 153);
		}
		myEllipseS(x + 4, y + 4, x + 41, y + 41, 200, 23, 35);

	}
	else
	{
		Block::print();
	}
}
int MineBlock::getN()
{
	return 4;
}