//#include<iostream>
#include "main.h"
int main() {
	/////장치 초기화 하기/////////
	initGraphic();
	initKey();
	initTimer();
	initPool();		//게임 오브젝트 관리 풀을 초기화함

	system("mode 100, 80");							//콘솔창 크기 조정

	addGameObj(new Player());
	addGameObj(new Enemy());

	//getSize();	//풀에 들어있는 오브젝트 갯수
	///////업데이트 반복/////////	
	while (true) {
		clear(0, 0, 255);
		updateKey();
		updateTimer();

		///////////////////
		//게임객체 업데이트	
		for (int i = 0; i < getSize(); i++)
		{
			GameObject* o = getGameObj(i); // 객체를 받아옴 0번부터 getSize까지
			if (o != NULL)
			{
				o->update(); // 받아온 객체를 업데이트
				if (o->getName() == "Player") 
				{
					if (o->getKeyCode() == VK_SPACE) 
					{
						addGameObj(new PLaser(o->getPx(), o->getPy()));
					}
				}	
				o->render();
			}
		}
		render();
		deleteArray();
	}
	return 0;
}