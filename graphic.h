#pragma once
#include <Windows.h>
#include <math.h>
#include"DDS.h"

#define STARTX   0  //그래픽 화면의 시작
#define STARTY   0    //그래픽 화면의 시작
#define WIDTH  480    //그래픽 화면의 가로 크기
#define HEIGHT 720    //그래픽 화면의 세로 크기

//#define GRAPHIC_MODE_0

void initGraphic();
void clear(int r, int g, int b);
void render();
void setPixel(int x, int y, int r, int g, int b);
void drawLine(int x0, int y0, int x1, int y1, int r, int, int b);
void drawCircle(int cx, int cy, int radius, int r, int g, int b);

unsigned int getPixel(int x, int y);
inline void getARGB(unsigned int color, unsigned char* a, unsigned char*r, unsigned char* g, unsigned char* b);
inline unsigned int makeARGB(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
inline unsigned int pixelBlierp(unsigned int c00, unsigned int c10, unsigned int c01, unsigned int c11, float dx, float dy);
unsigned int alphaBlending(unsigned int c0, unsigned int c1);