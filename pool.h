#pragma once
#include "header.h"
#define MAX 100

void initPool();
void addGameObj(GameObject* o);
void deleteGameObj(int index);
void deleteArray();
int getSize();
void minus_size();
GameObject* getGameObj(int i);

extern GameObject* obj[MAX];	//Max는 배열의 최대 크기
extern int arraySize;				//size는 현재까지 추가된 오브젝트의 갯수