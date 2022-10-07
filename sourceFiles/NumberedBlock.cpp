#include "NumberedBlock.h"
#include "help.h"
int NumberedBlock::getN()
{
	return n;
}
void NumberedBlock::increaseN()
{
	n++;
	type = "NumberedBlock";
}
NumberedBlock::NumberedBlock()
{
	type = "EmptyBlock";
}
void NumberedBlock::print()
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
		if (n == 1) {
			myLine(x + 22, y + 8, x + 22, y + 32, 10, 10, 10);
			myLine(x + 15, y + 15, x + 22, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
		}
		else if (n == 2) {
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
			myLine(x + 30, y + 8, x + 30, y + 20, 10, 10, 10);
			myLine(x + 12, y + 20, x + 12, y + 32, 10, 10, 10);
			myLine(x + 12, y + 20, x + 30, y + 20, 10, 10, 10);
		}
		else if (n == 3) {
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
			myLine(x + 30, y + 8, x + 30, y + 20, 10, 10, 10);
			myLine(x + 30, y + 20, x + 30, y + 32, 10, 10, 10);
			myLine(x + 14, y + 20, x + 30, y + 20, 10, 10, 10);

		}
		else if (n == 4)
		{
			x += 4;
			myLine(x + 22, y + 8, x + 22, y + 32, 10, 10, 10);
			myLine(x + 10, y + 25, x + 10, y + 8, 10, 10, 10);
			myLine(x + 12, y + 25, x + 30, y + 25, 10, 10, 10);
			x -= 4;
		}
		else if (n== 5)
		{
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
			myLine(x + 12, y + 8, x + 12, y + 20, 10, 10, 10);
			myLine(x + 30, y + 20, x + 30, y + 32, 10, 10, 10);
			myLine(x + 12, y + 20, x + 30, y + 20, 10, 10, 10);
		}

		else if (n == 6)
		{
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
			myLine(x + 12, y + 8, x + 12, y + 20, 10, 10, 10);
			myLine(x + 12, y + 20, x + 12, y + 32, 10, 10, 10);
			myLine(x + 30, y + 20, x + 30, y + 32, 10, 10, 10);
			myLine(x + 12, y + 20, x + 30, y + 20, 10, 10, 10);

		}

		else if (n== 7)
		{
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 30, y + 8, x + 18, y + 32, 10, 10, 10);

		}

		else if (n == 8)
		{
			myLine(x + 12, y + 8, x + 30, y + 8, 10, 10, 10);
			myLine(x + 12, y + 32, x + 30, y + 32, 10, 10, 10);
			myLine(x + 12, y + 8, x + 12, y + 20, 10, 10, 10);
			myLine(x + 12, y + 20, x + 12, y + 32, 10, 10, 10);
			myLine(x + 30, y + 20, x + 30, y + 32, 10, 10, 10);
			myLine(x + 30, y + 8, x + 30, y + 20, 10, 10, 10);
			myLine(x + 12, y + 20, x + 30, y + 20, 10, 10, 10);

		}
		
	}
	else
	{
		Block::print();
	}
}