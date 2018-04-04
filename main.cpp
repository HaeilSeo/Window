//#include<iostream>
#include "main.h"
int main() {
	/////��ġ �ʱ�ȭ �ϱ�/////////
	initGraphic();
	initKey();
	initTimer();
	initPool();		//���� ������Ʈ ���� Ǯ�� �ʱ�ȭ��

	system("mode 100, 80");							//�ܼ�â ũ�� ����

	addGameObj(new Player());
	addGameObj(new Enemy());

	//getSize();	//Ǯ�� ����ִ� ������Ʈ ����
	///////������Ʈ �ݺ�/////////	
	while (true) {
		clear(0, 0, 255);
		updateKey();
		updateTimer();

		///////////////////
		//���Ӱ�ü ������Ʈ	
		for (int i = 0; i < getSize(); i++)
		{
			GameObject* o = getGameObj(i); // ��ü�� �޾ƿ� 0������ getSize����
			if (o != NULL)
			{
				o->update(); // �޾ƿ� ��ü�� ������Ʈ
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