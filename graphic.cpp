#include"graphic.h"
#include<math.h> //sqrt ���� �Լ� ��� ����

void drawLine(int x0, int y0, int x1, int y1, unsigned int col) {
	int temp1;
	int temp2;

	//���� �׸��� ������ �Ǵ��Ͽ�, ���� �׸����̸�....
	if (y0 == y1) {
		//������(x0,y0)�� ����(x1, y1)���� �������̸� ������ �������� �ٲ۴�.
		if (x0 > x1) {
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}
	
		//���� �׸����Ѵ�
		for (int x = x0; x <= x1; x++) {
			Direct2D::setPixel(x, y0, col);
		}
	}
	//������ �׸��������� �Ǵ��Ѵ�, ������ �׸��� �̸�...
	else if (x0 == x1) {
		//������(x0,y0)�� ����(x1,y1)���� �Ʒ����̸� ������ �������� �ٲ۴�.
		if (y0 > y1) {
			temp1 = x0;
			x0 = x1;
			x1 = temp1;

			temp2 = y0;
			y0 = y1;
			y1 = temp2;
		}
		//������ �׸����Ѵ�.
		for (int y = y0; y <= y1; y++) {
			Direct2D::setPixel(x0, y, col);
		}
	}
	else {
		float m = (float)(y1 - y0) / (float)(x1 - x0);

		//���Ⱑ -1���� + 1���̿� �ִ��� �Ǵ��Ͽ� ���Ⱑ -1���� +1 �����̸�..
		if (-1 <= m && m <= 1) {
			//������(x0,y0)�� ����(x1,y1)���� �������̸�.. ������ �������� �ٲ۴�.
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
		//������ ����̸�..���Ⱑ -1����, +1�̻��� �����̸�
		else {
			//������(x0,y0)�� ����(x1,y1)���� �Ʒ����̸�.. ������ �������� �ٲ۴�.
			if (y0 > y1) {
				temp1 = x0;
				x0 = x1;
				x1 = temp1;
				
				temp2 = y0;
				y0 = y1;
				y1 = temp2;
			}
			//���Ⱑ -1����, +1�̻��� ������ �׸���.
			for (int y = y0; y <= y1; y++) {
				Direct2D::setPixel((int)(x0+(y - y0) * 1 / m + 0.5), y, col);
			}
		}
	}
}

void drawCircle(int cx, int cy, int r, unsigned int col) {
	int x = 0, y = 0;

	for (x = 0; x <= y; x++) {
		y = (int)(sqrt(r*r - x * x) + 0.5);	//y�� ��ǥ�� ����Ѵ�.
	
		Direct2D::setPixel(cx + x, cy + y, col); //���� ��ǥ�� �ȼ��� ����Ѵ�.
		Direct2D::setPixel(cx + x, cy - y, col); //�ȼ� ����� ����(cx,cy)��ŭ
		Direct2D::setPixel(cx - x, cy + y, col); //���� �̵� ��Ų��.
		Direct2D::setPixel(cx - x, cy - y, col);
		Direct2D::setPixel(cx + y, cy + x, col);	
		Direct2D::setPixel(cx + y, cy - x, col);
		Direct2D::setPixel(cx - y, cy + x, col);
		Direct2D::setPixel(cx - y, cy - x, col);
	}
}

//�簢�� �׸��� �Լ�
void drawRect(int x0, int y0, int x1, int y1, unsigned int col) {
	drawLine(x0, y0, x1, y0, col);
	drawLine(x0, y1, x1, y1, col);

	drawLine(x0, y0, x0, y1, col);
	drawLine(x1, y0, x1, y1, col);
}

//�ٰ��� �׸���
void drawPolygon(int* x, int* y, int n, unsigned int col) {
	for (int i = 0; i < n - 1; i++) {
		drawLine(x[i], y[i], x[i + 1], y[i + 1], col);
	}
	drawLine(x[n - 1], y[n - 1], x[0], y[0], col);
}
