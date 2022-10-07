#pragma once
void gotoxy(int x, int y);
void myRect(int x1, int y1, int x2, int y2, int R, int G, int B);
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B);
void myEllipseS(int x1, int y1, int x2, int y2, int R, int G, int B);
void myEllipseN(int x1, int y1, int x2, int y2, int R, int G, int B,int l);
void myLine(int x1, int y1, int x2, int y2, int R, int G, int B);
void myLineN(int x1, int y1, int x2, int y2, int R, int G, int B);
void myLineL(int x1, int y1, int x2, int y2, int R, int G, int B, int l);
void myRects(int x1, int y1, int x2, int y2, int R, int G, int B);
void myRectL(int x1, int y1, int x2, int y2, int R, int G, int B, int L);
bool getRowColbyLeftClick(int& rpos, int& cpos,int&);
void over();