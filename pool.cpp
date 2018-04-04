#include"pool.h"

GameObject* obj[MAX];	//Max�� �迭�� �ִ� ũ��
int arraySize;				//size�� ������� �߰��� ������Ʈ�� ����
void initPool() {

	////Ǯ �ʱ�ȭ �Լ�////
	for(int i=0; i<MAX; i++){
		obj[i] = NULL;	//NULL �� ���� ������Ʈ�� ��� ���� ����
	}              

	////Ǯ�� ���ڸ��� �����ϴ� ����////
	arraySize = 0;
}
void deleteArray()
{
	for (int i = 0; i < getSize(); ) // 3
	{
		if (obj[i]->getAlive() == false)
		{
			//����� 
			deleteGameObj(i);
			//delete obj[i];
			//obj[i] = NULL;
			printf("                                                             delete = %d\n", arraySize);
			for (int k = i; k <= getSize()-1; k++) {
				obj[k] = obj[k + 1];
			}	
			minus_size();
		}
		else {
			i++;
		}
	}
}
void deleteGameObj(int index) {
	delete obj[index];
	obj[index] = NULL;

}


void addGameObj(GameObject* o) {

  	if (arraySize < MAX) {  //�ִ� Ǯ�� ������ Ȯ��

		obj[arraySize] = o;

		obj[arraySize]->init();	 //���Ӱ�ü�� ���ӿ� �߰��Ǿ ������
	//	printf("                                                             create = %d\n", arraySize);
		arraySize++;
		
	}
	
}



int getSize() {

	return arraySize;		//������� �迭�� ��� �ִ� ��ü ����

}

void minus_size() {
	arraySize--;
}

GameObject* getGameObj(int i) {

	if (i < arraySize) {
		return obj[i];
	}
	else {				//���� i�� size���� ������ ���� ��������� �ʾ����� �������� NULL�� �־��ش�.
		return NULL;
	}
}