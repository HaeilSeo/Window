#include"graphic.h"
#include<math.h> //sqrt 수학 함수 헤더 파일

void drawLine(int x0, int y0, int x1, int y1, unsigned int col) {
	int temp1;
	int temp2;

	//수평선 그리기 인지를 판단하여, 수평선 그리기이면....
	if (y0 == y1) {
		//시작점(x0,y0)이 끝점(x1, y1)보다 오른쪽이면 끝점과 시작점을 바꾼다.
		if (x0 > x1) {
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}
	
		//수평선 그리기한다
		for (int x = x0; x <= x1; x++) {
			Direct2D::setPixel(x, y0, col);
		}
	}
	//수직선 그리기인지를 판단한다, 수직선 그리기 이면...
	else if (x0 == x1) {
		//시작점(x0,y0)이 끝점(x1,y1)보다 아래쪽이면 끝점과 시작점을 바꾼다.
		if (y0 > y1) {
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}
		//수직선 그리기한다.
		for (int y = y0; y <= y1; y++) {
			Direct2D::setPixel(x0, y, col);
		}
	}
	else {
		float m = (float)(y1 - y0) / (float)(x1 - x0);

		//기울기가 -1에서 + 1사이에 있는지 판단하여 기울기가 -1에서 +1 사이이면..
		if (-1 <= m && m <= 1) {
			//시작점(x0,y0)이 끝점(x1,y1)보다 오른쪽이면.. 끝점과 시작점을 바꾼다.
			if (x0 > x1) {
				temp1 = x0;
				x0 = x1;
				x1 = temp1;

				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}
			for (int x = x0; x <= x1; x++) {
				Direct2D::setPixel(x, (int)(y0 + (x - x0)*m + 0.5), col);
			}
		}
		//나머지 경우이면..기울기가 -1이하, +1이상인 직선이면
		else {
			//시작점(x0,y0)이 끝점(x1,y1)보다 아래쪽이면.. 끝점과 시작점을 바꾼다.
			if (y0 > y1) {
				temp1 = x0;
				x0 = x1;
				x1 = temp1;
				
				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}
			//기울기가 -1이하, +1이상인 직선을 그린다.
			for (int y = y0; y <= y1; y++) {
				Direct2D::setPixel((int)(x0+(y - y0) * 1 / m + 0.5), y, col);
			}
		}
	}
}

void drawCircle(int cx, int cy, int r, unsigned int col) {
	int x = 0, y = 0;

	for (x = 0; x <= y; x++) {
		y = (int)(sqrt(r*r - x * x) + 0.5);	//y축 좌표를 계산한다.
	
		Direct2D::setPixel(cx + x, cy + y, col); //계산된 좌표에 픽셀을 출력한다.
		Direct2D::setPixel(cx + x, cy - y, col); //픽셀 출력은 원점(cx,cy)만큼
		Direct2D::setPixel(cx - x, cy + y, col); //평행 이동 시킨다.
		Direct2D::setPixel(cx - x, cy - y, col);
		Direct2D::setPixel(cx + y, cy + x, col);	
		Direct2D::setPixel(cx + y, cy - x, col);
		Direct2D::setPixel(cx - y, cy + x, col);
		Direct2D::setPixel(cx - y, cy - x, col);
	}
}

//사각형 그리기 함수
void drawRect(int x0, int y0, int x1, int y1, unsigned int col) {
	drawLine(x0, y0, x1, y0, col);
	drawLine(x0, y1, x1, y1, col);

	drawLine(x0, y0, x0, y1, col);
	drawLine(x1, y0, x1, y1, col);
}

//다각형 그리기
void drawPolygon(int* x, int* y, int n, unsigned int col) {
	for (int i = 0; i < n - 1; i++) {
		drawLine(x[i], y[i], x[i + 1], y[i + 1], col);
	}
	drawLine(x[n - 1], y[n - 1], x[0], y[0], col);
}
