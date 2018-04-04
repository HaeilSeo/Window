#include"keyboard.h"
float prevTime; //���� �������� ���� �ð� 
float currTime; //���� �������� ���� �ð� 
float deltaTime; //���� �����Ӱ� ���� �������� �ð� ����
enum KeyState { KEY_UP_REP = 0, KEY_DOWN, KEY_DOWN_REP, KEY_UP };
KeyState keyState[256];

void initKey() {
	for (int i = 0; i < 256; i++) {
		keyState[i] = KeyState::KEY_UP_REP; //��� Ű�� ���� �������� �ʱ� ���¸� ������. 
	}
}

void updateKey() {
	for (int i = 0; i < 256; i++) {
		int key = GetAsyncKeyState(i);
		if (keyState[i] == KeyState::KEY_UP_REP) {
			if ((key & 0x8000) == 0x8000) {
				keyState[i] = KEY_DOWN;
			}
			else {
				keyState[i] = KEY_UP_REP;
			}
		}
		else if (keyState[i] == KeyState::KEY_DOWN) {
			if ((key & 0x8000) == 0x8000) {
				keyState[i] = KEY_DOWN_REP;
			}
			else {
				keyState[i] = KEY_UP;
			}
		}
		else if (keyState[i] == KeyState::KEY_DOWN_REP) {
			if ((key & 0x8000) == 0x8000) {
				keyState[i] = KEY_DOWN_REP;
			}
			else {
				keyState[i] = KEY_UP;
			}
		}
		else if (keyState[i] == KeyState::KEY_UP) {
			if ((key & 0x8000) == 0x8000) {
				keyState[i] = KEY_DOWN;
			}
			else {
				keyState[i] = KEY_UP_REP;
			}
		}
	}
}
//Ű�� ���������� ������ �ִ����� �˻��Ѵ�. 
bool GetKey(int keyCode) {
	if (keyState[keyCode] == KEY_DOWN_REP) {
		return true;
	}
	else {
		return false;
	}
}
bool GetKeyDown(int keyCode) {
	if (keyState[keyCode] == KEY_DOWN) {
		return true;
	}
	else {
		return false;
	}
}
void initTimer() {
	prevTime = (float)(GetTickCount() / 1000.0);
	//GetTickCount�� ��ǻ�Ͱ� ���õǸ鼭 �ð��� �����ǰ�(���ý� ���� 0) ���������� �и��������̴�(�� 1000�� 1����) 
	currTime = prevTime;
	deltaTime = 0;
}
void updateTimer() {
	currTime = (float)(GetTickCount() / 1000.0); //���� �ð��� �����Ѵ�. 
	deltaTime = currTime - prevTime; //���� �����Ӱ��� �ð� ���̸� �����Ѵ�. 
	prevTime = currTime; //���� ������ �ð��� ���� ������ ������ ����ȴ�. 

}
float getDeltaTime() {
	return deltaTime;
}


void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void hide() {
	CONSOLE_CURSOR_INFO ConsoleCursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
	ConsoleCursor.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); //���氪 ���� 
}
