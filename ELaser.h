#pragma once
#include "header.h"

class ELaser :public GameObject {
private:
	float speed;
	
public:
	ELaser(float px,float py);
	virtual ~ELaser();	//객체 생성 위치를 생성자로.. 받아올 수도 있음

	virtual void init();
	virtual void update();
};