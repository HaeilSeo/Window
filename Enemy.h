#pragma once
#include "header.h"
//#include<iostream>

class Enemy : public GameObject {
private:
	//���� ����
	float speed;
	float fireRate;
	float fireTime;
public:
	Enemy();
	virtual ~Enemy();
	virtual void init();
	virtual void update();
};