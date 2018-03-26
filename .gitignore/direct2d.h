#pragma once
#include<ddraw.h>

class Direct2D {
private:
	static HWND hWnd;		//윈도우 핸들
	static unsigned *BackBuffer;	//백 버퍼 주소

	static IDirectDraw7 *IDirectDraw; //DirectDraw 장치 주소 저장 포인터
	static IDirectDrawSurface7 *IDDPriSurf;	//화면 출력 버퍼 객체(COM)주소(인터페이스)저장 포인터
	static IDirectDrawSurface7 *IDDBackSurf;//그림 그리기 버퍼 객체(COM)주소(인터페이스)저장 포인터

	static int width;		//백버퍼의 실제 가로 크기
	static int height;	    //백버퍼의 실제 세로 크기

public:

	static bool init(int width, int height, HWND hWnd);	//그래픽 초기화 메소드
	static void exit();									//그래픽 종료 메소드
	static void clear(unsigned int col);				//화면지우기 - 백버퍼를 지움
	static void render();								//백 버퍼를 화면으로 출력

	static void setPixel(int x, int y, unsigned int col); //픽셀 출력
	static unsigned int getPixel(int x, int y);			  //픽셀 가져오기

	static HWND getHwnd();								  //윈도우 핸들 가져오기

};