#pragma once
#include "header.h"
//#include<iostream>

class Enemy : public GameObject {
private:
	//적기 변수
	float speed;
	float fireRate;
	float fireTime;
public:
	Enemy();
	virtual ~Enemy();
	virtual void init();
	virtual void update();
};