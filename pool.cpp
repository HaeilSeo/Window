#include"pool.h"

GameObject* obj[MAX];	//Max는 배열의 최대 크기
int arraySize;				//size는 현재까지 추가된 오브젝트의 갯수
void initPool() {

	////풀 초기화 함수////
	for(int i=0; i<MAX; i++){
		obj[i] = NULL;	//NULL 은 아직 오브젝트가 들어 있지 않음
	}              

	////풀에 빈자리를 지정하는 변수////
	arraySize = 0;
}
void deleteArray()
{
	for (int i = 0; i < getSize(); ) // 3
	{
		if (obj[i]->getAlive() == false)
		{
			//지우기 
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

  	if (arraySize < MAX) {  //최대 풀의 공간을 확인

		obj[arraySize] = o;

		obj[arraySize]->init();	 //게임객체가 게임에 추가되어서 시작함
	//	printf("                                                             create = %d\n", arraySize);
		arraySize++;
		
	}
	
}



int getSize() {

	return arraySize;		//현재까지 배열에 들어 있는 객체 갯수

}

void minus_size() {
	arraySize--;
}

GameObject* getGameObj(int i) {

	if (i < arraySize) {
		return obj[i];
	}
	else {				//만약 i가 size보다 작으면 아직 만들어지지 않았음을 뜻함으로 NULL을 넣어준다.
		return NULL;
	}
}