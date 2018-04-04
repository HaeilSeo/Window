#include"keyboard.h"
float prevTime; //이전 프레임의 시작 시간 
float currTime; //현재 프레임의 시작 시간 
float deltaTime; //현재 프레임과 이전 프레임의 시간 간격
enum KeyState { KEY_UP_REP = 0, KEY_DOWN, KEY_DOWN_REP, KEY_UP };
KeyState keyState[256];

void initKey() {
	for (int i = 0; i < 256; i++) {
		keyState[i] = KeyState::KEY_UP_REP; //모든 키는 놓임 지속으로 초기 상태를 가진다. 
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
//키를 지속적으로 누르고 있는지를 검사한다. 
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
	//GetTickCount는 컴퓨터가 부팅되면서 시간이 측정되고(부팅시 값은 0) 측정단위는 밀리세컨드이다(즉 1000이 1초임) 
	currTime = prevTime;
	deltaTime = 0;
}
void updateTimer() {
	currTime = (float)(GetTickCount() / 1000.0); //현재 시간을 측정한다. 
	deltaTime = currTime - prevTime; //이전 프레임과의 시간 차이를 측정한다. 
	prevTime = currTime; //현재 측정된 시간은 이전 프레임 값으로 저장된다. 

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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor); //변경값 적용 
}
