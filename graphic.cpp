#include "graphic.h"


//화면 출력이전에 그림을 그리는 백버퍼 배열임
unsigned int BackBuffer[HEIGHT][WIDTH];

unsigned int rgb(int r, int g, int b)
{
	unsigned int rgb = ((unsigned int)r) << 16 | ((unsigned int)g) << 8 | ((unsigned int)b) << 0;
	return rgb;
}

void setPixel(int x, int y, unsigned int col)
{
	//범위 검사 추가
	if (0 <= y && y <HEIGHT)  //y 좌표값을 검사
	{
		if (0 <= x && x < WIDTH)
		{
			BackBuffer[y][x] = col;
		}
	}
}

unsigned int getPixel(int x, int y)
{
	//범위 검사 추가
	if (0 <= y && y <HEIGHT)  //y 좌표값을 검사
	{
		if (0 <= x && x < WIDTH)
		{
			return BackBuffer[y][x];
		}
	}

	return 0;
}

void setPixel(int x, int y, int r, int g, int b)
{
	//범위 검사 추가
	if (0 <= y && y <HEIGHT)  //y 좌표값을 검사
	{
		if (0 <= x && x < WIDTH)
		{
			BackBuffer[y][x] = rgb(r, g, b);
		}
	}
}


void drawLine(int x0, int y0, int x1, int y1, unsigned int col)
{
	int temp1;
	int temp2;

	//(A)수평선 그리기 인지를 판단하여, 수평선 그리기이면 .... 
	if (y0 == y1)
	{
		//(A.a) 시작점(x0, y0) 이 끝점(x1, y1) 보다 오른쪽이면 끝점과 시작점을 바꾼다. 
		if (x0 > x1)
		{
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}

		//(A.b) 수평선 그리기한다. (위 그림의(1) 수평그리기 참고) 
		for (int x = x0; x <= x1; x++)
		{
			setPixel(x, y0, col);
		}
	}

	//(B) 수직선 그리기인지를 판단한다, 수직선 그리기 이면.... 
	else if (x0 == x1)
	{
		//(B.a) 시작점(x0, y0) 이 끝점(x1, y1) 보다 아래쪽 이면 끝점과 시작점을 바꾼다. 
		if (y0 > y1)
		{
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}

		//(B.b) 수직선 그리기한다. (위 그림의(3) 수직 그리기 참고) 
		for (int y = y0; y <= y1; y++)
		{
			setPixel(x0, y, col); //col 값은 각자가 선택함

		}

	}
	//﻿(C) 수직 / 수평선 그리기가 아니면..입력 점(시작점 끝점)으로 기울기를 구한다. (기울기 변수 는 실수형으로 함) 
	else
	{
		float m = (float)(y1 - y0) / (float)(x1 - x0);

		//(D) 기울기가 - 1 에서 + 1 사이에 있는지 판단하여...기울기가 - 1 에서 + 1 사이이면... 
		if (-1 <= m && m <= 1)
		{
			//(D.a) 시작점(x0, y0)이 끝점(x1, y1) 보다 오른쪽이면..끝점과 시작점을 바꾼다. 
			if (x0 > x1)
			{
				temp1 = x0;
				x0 = x1;
				x1 = temp1;

				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}

			//(D.b) 기울기가 - 1 ~+ 1 인 직선을 그린다. (위 그림(5) 번 그리기 참고) 
			for (int x = x0; x <= x1; x++)
			{
				setPixel(x, (int)(y0 + (x - x0)*m + 0.5), col);

			}

		}
		//(E) 나머지 경우이면..(기울기가 - 1 이하, +1 이상인 직선이면 
		else {

			//(E.a) 시작점(x0, y0)이 끝점(x1, y1) 보다 아래쪽이면..끝점과 시작점을 바꾼다.

			if (y0 > y1)
			{
				temp1 = x0;
				x0 = x1;
				x1 = temp1;

				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}

			//(E.b) 기울기가 - 1 이하, +1 이상인 직선을 그린다. (위 그림(7) 번 그리기 참고) 
			for (int y = y0; y <= y1; y++)
			{
				setPixel((int)(x0 + (y - y0) * 1 / m + 0.5), y, col); //col 값은 각자가 선택함 
			}

		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, int r, int g, int b)
{
	drawLine(x0, y0, x1, y1, rgb(r, g, b));
}

void drawCircle(int cx, int cy, int r, unsigned int col)
{
	int x = 0, y = 0;

	for (x = 0; x <= y; x++)
	{
		y = (int)(sqrt(r*r - x * x) + 0.5); // y 축 좌표를 계산한다.

		setPixel(cx + x, cy + y, col); //(1)계산된 (x,y) 좌표에 픽셀을 출력한다.
		setPixel(cx + x, cy - y, col); //(2)픽셀의 출력은 원점(cx, cy) 만큼 
		setPixel(cx - x, cy + y, col); // 평행 이동 시킨다.
		setPixel(cx - x, cy - y, col);
		setPixel(cx + y, cy + x, col);
		setPixel(cx + y, cy - x, col);
		setPixel(cx - y, cy + x, col);
		setPixel(cx - y, cy - x, col);
	}
}

void drawCircle(int cx, int cy, int radius, int r, int g, int b)
{
	drawCircle(cx, cy, radius, rgb(r, g, b));
}

///////////////////////////////////////////////////////////////////////////////////////////
//아래의 함수는 단순 실습용입니다. 게임 제작에 사용되지 않으므로..기능을 이용만함
///////////////////////////////////////////////////////////////////////////////

HWND hWnd = NULL;

void initGraphic()
{
	HWND GetConsoleHwnd();

	//커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	//그래픽 모들 핸들러를 구해옴
	hWnd = GetConsoleHwnd();
}

void clear(unsigned int col)
{
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			BackBuffer[j][i] = col; //배열을 지운다
		}
	}
}

void clear(int r, int g, int b)
{
	clear(rgb(r, g, b));
}

void render()
{
	HDC hDC, hMemDC;
	HBITMAP hBmp;
	void   * pBmp = NULL;
	int size;

	hDC = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	size = WIDTH * HEIGHT * 4;

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(BITMAPINFO));

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = WIDTH;
	bi.bmiHeader.biHeight = -HEIGHT;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = 0;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	hBmp = CreateDIBSection(hDC, &bi, DIB_RGB_COLORS, &pBmp, NULL, 0);
	SelectObject(hMemDC, hBmp);

	CopyMemory(pBmp, BackBuffer, size);

	BitBlt(hDC, STARTX, STARTY, WIDTH, HEIGHT, hMemDC, 0, 0, SRCCOPY);

	DeleteObject(hBmp);
	DeleteDC(hMemDC);
	DeleteObject(hDC);
}
inline void getARGB(unsigned int color, unsigned char* a, unsigned char* r, unsigned char* g, unsigned char* b) {
	*a = (color >> 24) & 0xff;
	*r = (color >> 16) & 0xff;
	*g = (color >> 8) & 0xff;
	*b = (color >> 0) & 0xff;
}
inline unsigned int makeARGB(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
	return (a << 24) || (r << 16) || (g << 8) || (b << 0);
}
inline unsigned int pixelBlierp(unsigned int c00, unsigned int c10, unsigned int c01, unsigned int c11, float dx, float dy) {
	unsigned char A[4];
	unsigned char B[4];
	unsigned char C[4];
	unsigned char D[4];

	getARGB(c00, &A[0], &A[1], &A[2], &A[3]);
	getARGB(c10, &B[0], &B[1], &B[2], &B[3]);
	getARGB(c01, &C[0], &C[1], &C[2], &C[3]);
	getARGB(c11, &D[0], &D[1], &D[2], &D[3]);
	float x1;
	float x2;
	float x[4];

	for (int i = 0; i < 4; i++) {
		x1 = A[i] * (1 - dx) + B[i] * dx;
		x2 = C[i] * (1 - dx) + D[i] * dx;

		x[i] = x1 * (1 - dy) + x2 * dy;
	}
	return makeARGB((unsigned char)x[0], (unsigned char)x[1], (unsigned char)x[2], (unsigned char)x[3]);
}
unsigned int getImagePixel(DDS_FILE* image, float x, float y) {
	float x0 = 0.0f;
	float y0 = 0.0f;

	float x1 = image->header.dwWidth - 2.0f;
	float y1 = image->header.dwHeight - 2.0f;

	if ((x1 >= x && x >= x0) && (y1 >= y && y >= y0)) {
		int xp = (int)floor(x);
		int yp = (int)floor(y);

		float dx = x - xp;
		float dy = y - yp;
		
		unsigned int A = image->data[(yp + 0)*image->header.dwWidth + (xp + 0)];
		unsigned int B = image->data[(yp + 0)*image->header.dwWidth + (xp + 1)];
		unsigned int C = image->data[(yp + 1)*image->header.dwWidth + (xp + 0)];
		unsigned int D = image->data[(yp + 1)*image->header.dwWidth + (xp + 1)];


		return pixelBlierp(A, B, C, D, dx, dy);
	
	}
	return 0x00000000;
}
unsigned int alphaBlending(unsigned int c0, unsigned int c1) {
	unsigned char C[4];
	unsigned char B[4];

	getARGB(c0, &C[0], &C[1], &C[2], &C[3]);
	getARGB(c1, &B[0], &B[1], &B[2], &B[3]);

	unsigned char A = C[0];
	unsigned char r = (unsigned char)((A*C[1] + (255 - A)*B[1])/ 255.0f);
	unsigned char g = (unsigned char)((A*C[2] + (255 - A)*B[2])/ 255.0f);
	unsigned char b = (unsigned char)((A*C[3] + (255 - A)*B[3])/ 255.0f);

	return makeARGB(B[0], r, g, b);
}

#ifdef GRAPHIC_MODE_0

HWND GetConsoleHwnd()
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	WCHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										 // WindowTitle.
	WCHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										  // WindowTitle.

										  // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}

#else

HWND GetConsoleHwnd()
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	CHAR pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
										// WindowTitle.
	CHAR pszOldWindowTitle[MY_BUFSIZE];  // Contains original
										 // WindowTitle.

										 // Fetch current window title.

	GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
	// Format a "unique" NewWindowTitle.

	wsprintf(pszNewWindowTitle, "%d/%d", GetTickCount(), GetCurrentProcessId());
	// Change current window title.

	SetConsoleTitle(pszNewWindowTitle);

	// Ensure window title has been updated.
	Sleep(40);

	// Look for NewWindowTitle.
	hwndFound = FindWindow(NULL, pszNewWindowTitle);

	// Restore original window title.
	SetConsoleTitle(pszOldWindowTitle);

	return(hwndFound);
}


#endif
