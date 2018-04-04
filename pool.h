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

extern GameObject* obj[MAX];	//Max�� �迭�� �ִ� ũ��
extern int arraySize;				//size�� ������� �߰��� ������Ʈ�� ����