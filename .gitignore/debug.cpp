#include<windows.h>
#include<tchar.h>
#include"debug.h"
#pragma warning(disable:4996)

void START_DEBUG_CONSOLE() {
	AllocConsole();			//�����쿡�� �ܼ�â �����ϱ� �Լ�
	
	freopen("CONOUT$", "w", stdout);	//printf �Ǵ� cout�� ���ؼ� ��µǴ� ǥ�� ���â���� ����
	freopen("CONIN$", "r", stdin);		//scanf_s �Ǵ� cin�� ���ؼ� �Է��� ���� �� �ִ� ǥ�� �Է� â���� ����
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

	if (hWnd != nullptr) {
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
	}
	START_DEBUG_CONSOLE();
	printf("����� �ܼ�â�� ���� �մϴ�.");

	///////������ �޽��� �ݺ� ó���ϱ�/////////
	MSG msg = { 0, };		//����� �Է� - �޴�/���콺/Ű���� ���� �̸�Ʈ(�޽���)�� �޾ƿ��� ����ü

	while (GetMessage(&msg, nullptr, 0, 0) == TRUE) {	//�ݺ������� ����ü������ �޽ø� �޾ƿ´�.
		TranslateMessage(&msg);					//�޽��� �������� �ʿ��� ó���� �Ѵ�.
		DispatchMessage(&msg);					//ó���� �޽����� �ش� ������ â�� �����Ѵ�.
	}
	////////�ܼ�â �����ϱ�////////////////////
	STOP_DEBUG_CONSOLE();
	return (int)msg.wParam;
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
