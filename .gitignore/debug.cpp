#include<windows.h>
#include<tchar.h>
#include"debug.h"
#pragma warning(disable:4996)

void START_DEBUG_CONSOLE() {
	AllocConsole();			//윈도우에서 콘솔창 시작하기 함수
	
	freopen("CONOUT$", "w", stdout);	//printf 또는 cout에 의해서 출력되는 표준 출력창으로 만듬
	freopen("CONIN$", "r", stdin);		//scanf_s 또는 cin에 의해서 입력을 받을 수 있는 표준 입력 창으로 만듬
}

void STOP_DEBUG_CONSOLE() {
	FreeConsole();			//윈도우에서 콘솔창 종료하기 함수
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam);


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPWSTR IpCmdLine, int nCmdShow) {
	///////윈도우 클래스  등록////////
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;	//윈도우 클래스 스타일 - 가로/세로 방향 그리기 스타일
	wcex.lpfnWndProc = WndProc;				//윈도우 창의 메뉴/마우스 이벤트 처리 함수 등록
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;				//이 윈도우 클래스를 관리하는 어플리케이션 인스턴스핸들
	wcex.hIcon = nullptr;					//아이콘 이미지 등록 - 현재 없음
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //커서 형태 등록 - 화살표 아이콘
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//윈도우 바탕색 지정
	wcex.lpszMenuName = nullptr;			//윈도우 메뉴 등록 - 현재 없음
	wcex.lpszClassName = L"MyWndClass";		//등록된 클래스의 이름 - 윈도우를 만들때 참조됨-L은 2바이트 문자열
	wcex.hIconSm = nullptr;					//작은 아이콘 등록 - 현재 없음

	RegisterClassExW(&wcex);


	HWND hWnd = CreateWindowW(L"MyWndClass",		//윈도우를 생성하기 위한 클래스 - 위에서 등록한 클래스
		L"윈도우창",			//생성되는 윈도우의 이름
		WS_OVERLAPPEDWINDOW,	//생성되는 윈도우의 형식 - 기존 위도우 형식임
		CW_USEDEFAULT,		//시작 위치와 윈도우 크기
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		hInstance,			//생성된 윈도우 창을 과닐하는 프로그램 인스턴스
		nullptr);

	if (hWnd != nullptr) {
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}
	START_DEBUG_CONSOLE();
	printf("디버기 콘솔창을 시작 합니다.");

	///////윈도우 메시지 반복 처리하기/////////
	MSG msg = { 0, };		//사용자 입력 - 메뉴/마우스/키보드 등의 이멘트(메시지)를 받아오는 구조체

	while (GetMessage(&msg, nullptr, 0, 0) == TRUE) {	//반복적으로 원영체제에서 메시를 받아온다.
		TranslateMessage(&msg);					//메시지 전잘전에 필요한 처리를 한다.
		DispatchMessage(&msg);					//처리된 메시지를 해당 윈도우 창에 전달한다.
	}
	////////콘솔창 종료하기////////////////////
	STOP_DEBUG_CONSOLE();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;	//윈도우 창 화면에 그리기를 할 정보를 저장하는 구조체
	HDC hdc;		//화면 그리기 장치 정보 핸드 -Device Context Handle

	switch (message) {
		case WM_COMMAND:
	//사용자 메뉴 입력 처리 부분
		break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);	//윈도우 종료 처리
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, IParam);
	}
	return 0;
}
