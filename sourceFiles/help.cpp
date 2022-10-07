#pragma once
#include <windows.h>
#include <iostream>
#include"help.h"
using namespace std;

bool getRowColbyLeftClick(int& rpos, int& cpos,int& whichbtn)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			POINT p;
			HWND hwnd = GetConsoleWindow();
			GetCursorPos(&p);

			if (ScreenToClient(hwnd, &p))
			{
				cpos = p.x * 1.5 + 2;
				rpos = p.y * 1.5 + 2;
				whichbtn = 1;
				return true;
			}
		}
		if (GetAsyncKeyState(VK_RBUTTON) & 1)
		{

			POINT p;
			HWND hwnd = GetConsoleWindow();
			GetCursorPos(&p);

			if (ScreenToClient(hwnd, &p))
			{
				cpos = p.x * 1.5 + 2;
				rpos = p.y * 1.5 + 2;
				whichbtn = 2;
				return true;
			}
		}
	} while (true);
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void myLine(int x1, int y1, int x2, int y2, int R, int G, int B) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 4, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}
void myLineN(int x1, int y1, int x2, int y2, int R, int G, int B) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 6, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}
void myLineL(int x1, int y1, int x2, int y2, int R, int G, int B, int l) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, l, RGB(R, G, B)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}


// This function checks if any of the 4 cursor keys are pressed. 
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.
bool isCursorKeyPressed(int& whichKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whichKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whichKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(39);
	if (key == 1)
	{

		whichKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whichKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(13);
	if (key == 1)
	{

		whichKey = 5;   // 4 if enter key is pressed
		return true;
	}
	return false;
}

void myRect(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	//HBRUSH brush = ::CreateSolidBrush(RGB(0,0, 0)); //Fill color is passed as parameter to the function!!!
	HBRUSH brush = (HBRUSH)::GetStockObject(NULL_BRUSH);//To make a transparent brush
	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myRectL(int x1, int y1, int x2, int y2, int R, int G, int B, int L)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, L, RGB(R, G, B));
	SelectObject(device_context, pen);
	//HBRUSH brush = ::CreateSolidBrush(RGB(0,0, 0)); //Fill color is passed as parameter to the function!!!
	HBRUSH brush = (HBRUSH)::GetStockObject(NULL_BRUSH);//To make a transparent brush
	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myRects(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(R, G, B)); //Fill color is passed as parameter to the function!!!
	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}
void myEllipseS(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 5, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(204, 204, 204));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}
void myEllipseN(int x1, int y1, int x2, int y2, int R, int G, int B,int l)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, l, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(204, 204, 204));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}

void game(int x1, int y1, int x2, int y2) {
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 20, RGB(20,140,20)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}
void over() {
	game(50 + 650, 50 + 200, 125 + 650, 50 + 200);
	game(50 + 650, 50 + 200, 50 + 650, 200 + 200);
	game(50 + 650, 200 + 200, 100 + 650, 200 + 200);
	game(100 + 650, 200 + 200, 100 + 650, 150 + 200);
	game(75 + 650, 150 + 200, 125 + 650, 150 + 200);
	game(125 + 650, 150 + 200, 125 + 650, 200 + 200);
	game(175 + 650, 50 + 200, 150 + 650, 200 + 200);
	game(175 + 650, 50 + 200, 200 + 650, 200 + 200);
	game(175 + 650, 150 + 200, 175 + 650, 150 + 200);
	game(225 + 650, 50 + 200, 225 + 650, 200 + 200);
	game(225 + 650, 50 + 200, 275 + 650, 175 + 200);
	game(275 + 650, 175 + 200, 325 + 650, 50 + 200);
	game(325 + 650, 50 + 200, 325 + 650, 200 + 200);
	game(350 + 650, 50 + 200, 350 + 650, 200 + 200);
	game(350 + 650, 125 + 200, 425 + 650, 125 + 200);
	game(350 + 650, 50 + 200, 425 + 650, 50 + 200);
	game(350 + 650, 50 + 200, 425 + 650, 50 + 200);
	game(350 + 650, 200 + 200, 425 + 650, 200 + 200);
	game(50 + 650, 250 + 200, 50 + 650, 400 + 200);
	game(50 + 650, 250 + 200, 125 + 650, 250 + 200);
	game(50 + 650, 400 + 200, 125 + 650, 400 + 200);
	game(125 + 650, 400 + 200, 125 + 650, 250 + 200);
	game(150 + 650, 250 + 200, 175 + 650, 400 + 200);
	game(175 + 650, 400 + 200, 200 + 650, 250 + 200);
	game(225 + 650, 250 + 200, 225 + 650, 400 + 200);
	game(225 + 650, 250 + 200, 300 + 650, 250 + 200);
	game(225 + 650, 325 + 200, 300 + 650, 325 + 200);
	game(225 + 650, 400 + 200, 300 + 650, 400 + 200);
	game(350 + 650, 250 + 200, 350 + 650, 400 + 200);
	game(350 + 650, 250 + 200, 420 + 650, 250 + 200);
	game(420 + 650, 250 + 200, 420 + 650, 325 + 200);
	game(420 + 650, 325 + 200, 350 + 650, 325 + 200);
	game(375 + 650, 325 + 200, 420 + 650, 400 + 200);
}


