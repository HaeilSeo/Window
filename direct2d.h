#pragma once
#include<ddraw.h>

class Direct2D {
private:
	static HWND hWnd;		//������ �ڵ�
	static unsigned *BackBuffer;	//�� ���� �ּ�

	static IDirectDraw7 *IDirectDraw; //DirectDraw ��ġ �ּ� ���� ������
	static IDirectDrawSurface7 *IDDPriSurf;	//ȭ�� ��� ���� ��ü(COM)�ּ�(�������̽�)���� ������
	static IDirectDrawSurface7 *IDDBackSurf;//�׸� �׸��� ���� ��ü(COM)�ּ�(�������̽�)���� ������

	static int width;		//������� ���� ���� ũ��
	static int height;	    //������� ���� ���� ũ��

public:

	static bool init(int width, int height, HWND hWnd);	//�׷��� �ʱ�ȭ �޼ҵ�
	static void exit();									//�׷��� ���� �޼ҵ�
	static void clear(unsigned int col);				//ȭ������� - ����۸� ����
	static void render();								//�� ���۸� ȭ������ ���

	static void setPixel(int x, int y, unsigned int col); //�ȼ� ���
	static unsigned int getPixel(int x, int y);			  //�ȼ� ��������

	static HWND getHwnd();								  //������ �ڵ� ��������

};