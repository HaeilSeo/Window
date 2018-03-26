#include"direct2d.h"
#include"graphic.h"
#include<stdio.h>
#define WIDTH 480
#define HEIGHT 750
///////DirectDraw ���̺귯�� �߰�///////////

#pragma comment(lib,"ddraw.lib")	//DirectDraw �Լ� ���̺귯��
#pragma comment(lib,"dxguid.lib")	//DirectDraw ID ���� ���̺귯��

//DirectDraw�� ����ϱ� ���ؼ��� ���̺귯���� �߰��ؾ� �Ѵ�. "ddraw.lib"��
//DirectDraw�� ����� �� �ִ� ��� ����� �����ϰ�, "dxguid.lib"�� �׷��� ��ġ/���۸� 
//�����ϱ� ���Ͽ� ���̵� ������ ������ �ش�.

HWND Direct2D::hWnd = NULL;		//������ �ڵ�
unsigned int* Direct2D::BackBuffer = NULL;	//�� ���� �ּ� ���� ������

IDirectDraw7* Direct2D::IDirectDraw = NULL;	//DirectDraw ��ġ �ּ� ���� ������
IDirectDrawSurface7* Direct2D::IDDPriSurf = NULL; //ȭ�� ��� ���� ��ü(COM)�ּ�(�������̽�)���� ������
IDirectDrawSurface7* Direct2D::IDDBackSurf = NULL; //�׸� �׸��� ���� ��ü(COM)�ּ�(�������̽�)���� ������

int Direct2D::width = 0; //���۹��� ���� ���� ũ��
int Direct2D::height = 0; //������� ���� ���� ũ��

//C++���� Ŭ���� �ȿ� ����� ���� ��� ������ ������ ������ ����� ������ �ʴ´�.
//��, (������ ���� ������ ����). ���� ������ ����� ���ؼ��� Ŭ���� �ܺο��� ������ �����ϰ� �ʿ��ϸ� �ʱ�ȭ �ؾ� �Ѵ�.

bool Direct2D::init(int width, int height, HWND hWnd) {
	//���޵� ������ Ŭ������ ���� ������ �����Ѵ�. - �����ϰ� ���Ŀ� �ʿ��� �� �����
	Direct2D::width = width;
	Direct2D::height = height;
	Direct2D::hWnd = hWnd;

	HRESULT hr;		//HRESULT�� �����쿡�� ����ϴ� �Լ� ����/���� ��ȯ ����Ÿ ����

	//DirectDraw ��ġ�� �����ϰ� ������ ��ġ �����͸� �����Ѵ�.
	hr = DirectDrawCreateEx(NULL,	//GUID�� ���� ��ȯ ����
							(LPVOID*)&(Direct2D::IDirectDraw),	//��ü �������̽�(������)�� ��ȯ ����
							IID_IDirectDraw7,					//DirectDraw7 ���� ���̵� - dxguid.lib�� �����
							NULL);
	if (FAILED(hr)) {	//FAILED�� HRESULT�� ��ȯ�� ���� ���� ������ üũ�ϴ� ��ũ�� �Լ���
		printf("DirectDraw7 ��ġ ���� ����");
		return false;
	}

	//������ DirectDraw�� �׸��� ����� ������ â�� ����Ǿ�� �Ѵ�. SetCooperativeLevel �� ��ġ�� ������ â�� ���� �Ǿ ����
	//���� �����ϴ� ����� �����Ѵ�.
	hr = Direct2D::IDirectDraw->SetCooperativeLevel(Direct2D::hWnd, DDSCL_NORMAL);

	if (FAILED(hr)) {
		printf("���� ���� ���� ����");
		return false;
	}

	//ȭ�� ��� ���� - Primary Surface �����
	DDSURFACEDESC2 DESC;
	ZeroMemory(&DESC, sizeof(DESC));	//ZeroMemory�� Ư�� �޸� ������ 0�� �ʱ�ȭ ���ִ� Window API �Լ���

	DESC.dwSize = sizeof(DESC);	
	DESC.dwFlags = DDSD_CAPS;			//ddsCaps ����ü�� �����
	DESC.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;	//�����̸Ӹ� Surface�� ����

	hr = Direct2D::IDirectDraw->CreateSurface(&DESC, &Direct2D::IDDPriSurf, NULL);
	if (FAILED(hr)) {
		printf("�����̸Ӹ� ���ǽ� ���� ����");
		return false;
	}

	//�׸� �׸��� �� ���� - Back Surface �����
	ZeroMemory(&DESC, sizeof(DESC));

	DESC.dwSize = sizeof(DESC);
	DESC.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
	DESC.dwWidth = Direct2D::width;
	DESC.dwHeight = Direct2D::height;
	DESC.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

	DESC.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	DESC.ddpfPixelFormat.dwFlags = DDPF_RGB;
	DESC.ddpfPixelFormat.dwRGBBitCount = 32;	//�ȼ��� ��Ʈ ũ�� (32��Ʈ - 4����Ʈ)
	DESC.ddpfPixelFormat.dwRBitMask = 0x00FF0000;	//�ȼ����� R �� ��ġ
	DESC.ddpfPixelFormat.dwGBitMask = 0x0000FF00;	//�ȼ����� G �� ��ġ
	DESC.ddpfPixelFormat.dwBBitMask = 0x000000FF;	//�ȼ����� B �� ��ġ
	DESC.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000;	//�ȼ����� Alpha �� ��ġ

	hr = Direct2D::IDirectDraw->CreateSurface(&DESC, &(Direct2D::IDDBackSurf), NULL);

	if (FAILED(hr)) {
		printf("�� ���ǽ� ���� ����");
		return false;
	}
	return true;
}

void Direct2D::exit() {
	#define ReleaseCOM(x){if(x!=NULL)x->Release(); x=NULL;};

	ReleaseCOM(Direct2D::IDDBackSurf);
	ReleaseCOM(Direct2D::IDDPriSurf);
	ReleaseCOM(Direct2D::IDirectDraw);

	//DirectDraw ���� ���Ǵ� ��ü�� �Ϲ� C++ ��ü�ʹ� �ٸ� COM ��ü�� �����ȴ�.
	//COM ��ü�� ��ü���� �����ϴ� Release �޼ҵ带 ȣ���ؼ� 
	//��ü�� ������ �Ѵ�(COM ��ü�� delete�� ��� �� ������)
}

void Direct2D::render() {
	POINT pt;
	Direct2D::IDDBackSurf->Unlock(NULL); //����۸� ������ �� �ְ� ����� �����Ѵ�.
	
	pt.x = 0;
	pt.y = 0;

	ClientToScreen(Direct2D::hWnd, &pt);	//����� ������ ��ġ�� ���ؿ´�. - �޴�/�׵θ� ������ ������ �׸� ��� ���� ��ġ�� ����
	Direct2D::IDDPriSurf->BltFast(pt.x, pt.y, Direct2D::IDDBackSurf, NULL, 0);	//�� ������ ������ �����̸Ӹ� ���۷� �����Ѵ�.	
}

void Direct2D::setPixel(int x, int y, unsigned int col) {
	if( (Direct2D::height > y&&y >= 0) && (Direct2D::width > x&&x >= 0)){
		BackBuffer[y*Direct2D::width + x] = col;
	}
}

void Direct2D::clear(unsigned int col) {
	DDSURFACEDESC2 DESC;		//�� ������ ������ �������� ���� ����ü
	ZeroMemory(&DESC, sizeof(DESC));

	DESC.dwSize = sizeof(DESC);

	if (Direct2D::IDDBackSurf->Lock(NULL, &DESC, DDLOCK_WAIT, NULL) == DD_OK) {
		BackBuffer = (unsigned int*)DESC.lpSurface;
		
		Direct2D::width = DESC.dwLinearSize >> 2;	//���� ������ ũ�� DESC.dwLinearSize�� ����Ʈ ������
		Direct2D::height = DESC.dwHeight;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				BackBuffer[y*width + x] = col;
			}
		}	
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;	//������ â ȭ�鿡 �׸��⸦ �� ������ �����ϴ� ����ü 
	HDC hdc;		//ȭ�� �׸��� ��ġ ���� �ڵ� -Device Context Handle 


	switch (message) {
		case WM_COMMAND:
		//����� �޴� �Է� ó�� �κ� 
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		

	 	case WM_DESTROY:
			PostQuitMessage(0);	//������ ���� ó�� 
			break;
		default:
		return DefWindowProc(hWnd, message, wParam, IParam);	
	}
	return 0;
	
}



void START_DEBUG_CONSOLE() {
	AllocConsole();			//�����쿡�� �ܼ�â �����ϱ� �Լ� 
}


void STOP_DEBUG_CONSOLE() {
	FreeConsole();			//�����쿡�� �ܼ�â �����ϱ� �Լ� 

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam);


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPWSTR IpCmdLine, int nCmdShow) {
	
	///////������ Ŭ����  ���//////// 
	WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
	

 	wcex.style = CS_HREDRAW | CS_VREDRAW;	//������ Ŭ���� ��Ÿ�� - ����/���� ���� �׸��� ��Ÿ�� 
	wcex.lpfnWndProc = WndProc;				//������ â�� �޴�/���콺 �̺�Ʈ ó�� �Լ� ��� 
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;				//�� ������ Ŭ������ �����ϴ� ���ø����̼� �ν��Ͻ��ڵ� 
	wcex.hIcon = nullptr;					//������ �̹��� ��� - ���� ���� 
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //Ŀ�� ���� ��� - ȭ��ǥ ������ 
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//������ ������ ���� 
	wcex.lpszMenuName = nullptr;			//������ �޴� ��� - ���� ���� 
	wcex.lpszClassName = L"MyWndClass";		//��ϵ� Ŭ������ �̸� - �����츦 ���鶧 ������-L�� 2����Ʈ ���ڿ� 
	wcex.hIconSm = nullptr;					//���� ������ ��� - ���� ���� 

 	RegisterClassExW(&wcex);
	
	/*
	HWND hWnd = CreateWindowW(L"MyWndClass",		//�����츦 �����ϱ� ���� Ŭ���� - ������ ����� Ŭ���� 
	L"������â",			//�����Ǵ� �������� �̸� 
	WS_OVERLAPPEDWINDOW,	//�����Ǵ� �������� ���� - ���� ������ ������ 
	CW_USEDEFAULT,		//���� ��ġ�� ������ ũ�� 
	0,
	CW_USEDEFAULT,
	0,
	nullptr,
	nullptr,
	hInstance,			//������ ������ â�� �����ϴ� ���α׷� �ν��Ͻ� 
	nullptr);

	*/
	RECT rt;
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX; //������ ���� ��Ÿ�� ����

	rt.left = 0;
	rt.right = WIDTH;	//WIDTH�� ���� ȭ���� ���� ũ�� - DirectDraw ������ ���� ũ��
	rt.top = 0;
	rt.bottom = HEIGHT; //HEIGHT�� ���� ȭ���� ���� ũ�� - DirectDraw ������ ���� ũ��

						//AdjustWindowRect�� Ŭ���̾�Ʈ �������� ��ü ������ ũ�⸦ ������ش�.

	AdjustWindowRect(&rt, style, FALSE);	//WIDTH �� HEIGHT�� ȭ�� ũ��(Ŭ���̾�Ʈ ����)�� �ǵ��� ��������

	int windowWidth = rt.right - rt.left;	//AdjustWindowRect ���� ������ ������ ����ũ��
	int windowHeight = rt.bottom - rt.top;	//AdjustWindowRect ���� ������ ������ ����ũ��

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);	//ȭ�� ��ü�� ����ũ��
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);	//ȭ�� ��ü�� ����ũ��

	int startX = (screenWidth - windowWidth) / 2;	//�����찡 ȭ�� �߰��� ��ġ�ϵ��� ���� ��ġ�� �����
	int startY = (screenHeight - windowHeight) / 2;

	HWND hWnd = CreateWindowW(L"MyWndClass",		//�����츦 �����ϱ� ���� Ŭ���� - ������ ����� Ŭ���� 
		L"������â",			//�����Ǵ� �������� �̸� 
		style,				//������ ���� ȭ�� ��ġ - ȭ�� �߰��� ����
		startX,				//���� ��ġ�� ������ ũ�� 
		startY,
		windowWidth,		//������ ũ�� - ���� ��鿡 ���� ������ ������ ũ��
		windowHeight,
		nullptr,
		nullptr,
		hInstance,			//������ ������ â�� �����ϴ� ���α׷� �ν��Ͻ� 
		nullptr);

 	if (hWnd != nullptr) {
 		ShowWindow(hWnd, nCmdShow);
 		UpdateWindow(hWnd);

	}
	START_DEBUG_CONSOLE();
	printf("����� �ܼ�â�� ���� �մϴ�.");
	///////DirectDraw ����̽� �ʱ�ȭ////////
	Direct2D::init(WIDTH, HEIGHT, hWnd);

	///////������ �޽��� �ݺ� ó���ϱ�///////// 
	MSG msg = { 0, };		//����� �Է� - �޴�/���콺/Ű���� ���� �̸�Ʈ(�޽���)�� �޾ƿ��� ����ü 

	while (WM_QUIT!=msg.message) {	//�ݺ������� ����ü������ �޽ø� �޾ƿ´�. 
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);					//�޽��� �������� �ʿ��� ó���� �Ѵ�. 
			DispatchMessage(&msg);					//ó���� �޽����� �ش� ������ â�� �����Ѵ�. 
		}
		Direct2D::clear(0x000000FF);			//�� ���۸� �Ķ������� �ʱ�ȭ �Ѵ�.
		drawLine(0, 0, WIDTH, HEIGHT, 0x00ff0000);	//ù��° ����
		drawLine(WIDTH, 0, 0, HEIGHT, 0x00ff0000);	//�ι�° ����
		
		drawCircle(120, 150, 100, 0x0000ff00);
		drawRect(100, 200, 200, 400, 0x00000000);

		int x[3] = { 200,300,400 };
		int y[3] = { 500,100,500 };

		drawPolygon(x, y, 3, 0x0000ff00);
		Direct2D::render();						//�� ���۸� �����̸Ӹ� ���۷� ���� - ȭ�鿡 ��µȴ�.
	}
	/////////DirectDraw ����̽� ����//////////////
	Direct2D::exit();

	////////�ܼ�â �����ϱ�//////////////////// 
	STOP_DEBUG_CONSOLE();
	return (int)msg.wParam;
	
}
