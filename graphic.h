#pragma once
#include"direct2d.h"
void drawLine(int x0, int y0, int x1, int y1, unsigned int col);
void drawCircle(int cx, int cy, int r, unsigned int col);
void drawRect(int x0, int y0, int x1, int y1, unsigned int col);	//�簢�� �׸���
void drawPolygon(int* x, int* y, int n, unsigned int col);		//�ٰ��� �׸���	