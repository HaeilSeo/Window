#include"direct2d.h"
#include"graphic.h"
#include<stdio.h>
#define WIDTH 480
#define HEIGHT 750
///////DirectDraw 라이브러리 추가///////////

#pragma comment(lib,"ddraw.lib")	//DirectDraw 함수 라이브러리
#pragma comment(lib,"dxguid.lib")	//DirectDraw ID 저장 라이브러리

//DirectDraw를 사용하기 위해서는 라이브러리를 추가해야 한다. "ddraw.lib"는
//DirectDraw를 사용할 수 있는 모든 기능을 제고하고, "dxguid.lib"는 그래픽 장치/버퍼를 
//구분하기 위하여 아이디 정보를 제공해 준다.

HWND Direct2D::hWnd = NULL;		//윈도우 핸들
unsigned int* Direct2D::BackBuffer = NULL;	//백 버퍼 주소 저장 포인터

IDirectDraw7* Direct2D::IDirectDraw = NULL;	//DirectDraw 장치 주소 저장 포인터
IDirectDrawSurface7* Direct2D::IDDPriSurf = NULL; //화면 출려 버퍼 객체(COM)주소(인터페이스)저장 포인터
IDirectDrawSurface7* Direct2D::IDDBackSurf = NULL; //그림 그리기 버퍼 객체(COM)주소(인터페이스)저장 포인터

int Direct2D::width = 0; //백퍼버의 실제 가로 크기
int Direct2D::height = 0; //백버퍼의 실제 세로 크기

//C++에서 클래스 안에 선언된 정적 멤버 변수는 실제로 변수가 만들어 지지는 않는다.
//즉, (벽수가 정의 되지는 않음). 실제 변수를 만들기 위해서는 클래스 외부에서 변수를 정의하고 필요하면 초기화 해야 한다.

bool Direct2D::init(int width, int height, HWND hWnd) {
	//전달된 변수를 클래스의 정적 변수에 저장한다. - 저장하고 이후에 필요할 때 사용함
	Direct2D::width = width;
	Direct2D::height = height;
	Direct2D::hWnd = hWnd;

	HRESULT hr;		//HRESULT는 윈도우에서 사용하는 함수 성공/실패 반환 데이타 형임

	//DirectDraw 장치를 생성하고 생성된 장치 포인터를 저장한다.
	hr = DirectDrawCreateEx(NULL,	//GUID의 값을 반환 받음
							(LPVOID*)&(Direct2D::IDirectDraw),	//객체 인터페이스(포인터)를 반환 받음
							IID_IDirectDraw7,					//DirectDraw7 구분 아이디 - dxguid.lib에 저장됨
							NULL);
	if (FAILED(hr)) {	//FAILED는 HRESULT를 반환된 값이 실패 인지를 체크하는 매크로 함수임
		printf("DirectDraw7 장치 생성 실패");
		return false;
	}

	//생성된 DirectDraw는 그림을 출력할 윈도우 창과 연결되어야 한다. SetCooperativeLevel 은 장치와 윈도우 창이 연결 되어서 서로
	//협력 동작하는 방식을 결정한다.
	hr = Direct2D::IDirectDraw->SetCooperativeLevel(Direct2D::hWnd, DDSCL_NORMAL);

	if (FAILED(hr)) {
		printf("협력 레벨 설정 실패");
		return false;
	}

	//화면 출력 버퍼 - Primary Surface 만들기
	DDSURFACEDESC2 DESC;
	ZeroMemory(&DESC, sizeof(DESC));	//ZeroMemory는 특정 메모리 영역을 0을 초기화 해주는 Window API 함수임

	DESC.dwSize = sizeof(DESC);	
	DESC.dwFlags = DDSD_CAPS;			//ddsCaps 구조체를 사용함
	DESC.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;	//프라이머리 Surface를 만듬

	hr = Direct2D::IDirectDraw->CreateSurface(&DESC, &Direct2D::IDDPriSurf, NULL);
	if (FAILED(hr)) {
		printf("프라이머리 서피스 생성 실패");
		return false;
	}

	//그림 그리는 백 버퍼 - Back Surface 만들기
	ZeroMemory(&DESC, sizeof(DESC));

	DESC.dwSize = sizeof(DESC);
	DESC.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
	DESC.dwWidth = Direct2D::width;
	DESC.dwHeight = Direct2D::height;
	DESC.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

	DESC.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	DESC.ddpfPixelFormat.dwFlags = DDPF_RGB;
	DESC.ddpfPixelFormat.dwRGBBitCount = 32;	//픽셀의 비트 크기 (32비트 - 4바이트)
	DESC.ddpfPixelFormat.dwRBitMask = 0x00FF0000;	//픽셀에서 R 값 위치
	DESC.ddpfPixelFormat.dwGBitMask = 0x0000FF00;	//픽셀에서 G 값 위치
	DESC.ddpfPixelFormat.dwBBitMask = 0x000000FF;	//픽셀에서 B 값 위치
	DESC.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000;	//픽셀에서 Alpha 값 위치

	hr = Direct2D::IDirectDraw->CreateSurface(&DESC, &(Direct2D::IDDBackSurf), NULL);

	if (FAILED(hr)) {
		printf("백 서피스 생성 실패");
		return false;
	}
	return true;
}

void Direct2D::exit() {
	#define ReleaseCOM(x){if(x!=NULL)x->Release(); x=NULL;};

	ReleaseCOM(Direct2D::IDDBackSurf);
	ReleaseCOM(Direct2D::IDDPriSurf);
	ReleaseCOM(Direct2D::IDirectDraw);

	//DirectDraw 에서 사용되는 객체는 일반 C++ 객체와는 다른 COM 객체로 생성된다.
	//COM 객체는 객체에서 제공하는 Release 메소드를 호출해서 
	//객체를 지워야 한다(COM 객체는 delete는 사용 할 수없음)
}

void Direct2D::render() {
	POINT pt;
	Direct2D::IDDBackSurf->Unlock(NULL); //백버퍼를 전송할 수 있게 잠금을 해제한다.
	
	pt.x = 0;
	pt.y = 0;

	ClientToScreen(Direct2D::hWnd, &pt);	//출력할 영역의 우치를 구해온다. - 메뉴/테두리 영역을 제외한 그림 출력 영역 위치를 구함
	Direct2D::IDDPriSurf->BltFast(pt.x, pt.y, Direct2D::IDDBackSurf, NULL, 0);	//백 버퍼의 내용을 프라이머리 버퍼로 전송한다.	
}

void Direct2D::setPixel(int x, int y, unsigned int col) {
	if( (Direct2D::height > y&&y >= 0) && (Direct2D::width > x&&x >= 0)){
		BackBuffer[y*Direct2D::width + x] = col;
	}
}

void Direct2D::clear(unsigned int col) {
	DDSURFACEDESC2 DESC;		//백 버퍼의 정보를 가져오기 위한 구조체
	ZeroMemory(&DESC, sizeof(DESC));

	DESC.dwSize = sizeof(DESC);

	if (Direct2D::IDDBackSurf->Lock(NULL, &DESC, DDLOCK_WAIT, NULL) == DD_OK) {
		BackBuffer = (unsigned int*)DESC.lpSurface;
		
		Direct2D::width = DESC.dwLinearSize >> 2;	//내부 버퍼의 크기 DESC.dwLinearSize는 바이트 단위임
		Direct2D::height = DESC.dwHeight;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				BackBuffer[y*width + x] = col;
			}
		}	
	}
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



void START_DEBUG_CONSOLE() {
	AllocConsole();			//윈도우에서 콘솔창 시작하기 함수 
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
	
	/*
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

	*/
	RECT rt;
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; //윈도우 생성 스타일 변경

	rt.left = 0;
	rt.right = WIDTH;	//WIDTH는 게임 화면의 가로 크기 - DirectDraw 버퍼의 가로 크기
	rt.top = 0;
	rt.bottom = HEIGHT; //HEIGHT는 게임 화면의 세로 크기 - DirectDraw 버퍼의 세로 크기

						//AdjustWindowRect는 클라이언트 영역으로 전체 윈도우 크기를 계산해준다.

	AdjustWindowRect(&rt, style, FALSE);	//WIDTH 와 HEIGHT가 화면 크기(클라이언트 영영)가 되도록 재조정함

	int windowWidth = rt.right - rt.left;	//AdjustWindowRect 에서 구해진 윈도우 가로크기
	int windowHeight = rt.bottom - rt.top;	//AdjustWindowRect 에서 구해진 윈도우 세로크기

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);	//화면 전체의 가로크기
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);	//화면 전체의 세로크기

	int startX = (screenWidth - windowWidth) / 2;	//윈도우가 화면 중간에 위치하도록 시작 위치를 계산함
	int startY = (screenHeight - windowHeight) / 2;

	HWND hWnd = CreateWindowW(L"MyWndClass",		//윈도우를 생성하기 위한 클래스 - 위에서 등록한 클래스 
		L"윈도우창",			//생성되는 윈도우의 이름 
		style,				//윈도우 생성 화면 위치 - 화면 중간에 생성
		startX,				//시작 위치와 윈도우 크기 
		startY,
		windowWidth,		//윈도우 크기 - 게임 장면에 의해 수정된 위도우 크기
		windowHeight,
		nullptr,
		nullptr,
		hInstance,			//생성된 윈도우 창을 과닐하는 프로그램 인스턴스 
		nullptr);

 	if (hWnd != nullptr) {
 		ShowWindow(hWnd, nCmdShow);
 		UpdateWindow(hWnd);

	}
	START_DEBUG_CONSOLE();
	printf("디버깅 콘솔창을 시작 합니다.");
	///////DirectDraw 디바이스 초기화////////
	Direct2D::init(WIDTH, HEIGHT, hWnd);

	///////윈도우 메시지 반복 처리하기///////// 
	MSG msg = { 0, };		//사용자 입력 - 메뉴/마우스/키보드 등의 이멘트(메시지)를 받아오는 구조체 

	while (WM_QUIT!=msg.message) {	//반복적으로 원영체제에서 메시를 받아온다. 
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);					//메시지 전잘전에 필요한 처리를 한다. 
			DispatchMessage(&msg);					//처리된 메시지를 해당 윈도우 창에 전달한다. 
		}
		Direct2D::clear(0x000000FF);			//백 버퍼를 파란색으로 초기화 한다.
		drawLine(0, 0, WIDTH, HEIGHT, 0x00ff0000);	//첫번째 직선
		drawLine(WIDTH, 0, 0, HEIGHT, 0x00ff0000);	//두번째 직선
		
		drawCircle(120, 150, 100, 0x0000ff00);
		drawRect(100, 200, 200, 400, 0x00000000);

		int x[3] = { 200,300,400 };
		int y[3] = { 500,100,500 };

		drawPolygon(x, y, 3, 0x0000ff00);
		Direct2D::render();						//백 버퍼를 프라이머리 버퍼로 전송 - 화면에 출력된다.
	}
	/////////DirectDraw 디바이스 종료//////////////
	Direct2D::exit();

	////////콘솔창 종료하기//////////////////// 
	STOP_DEBUG_CONSOLE();
	return (int)msg.wParam;
	
}
