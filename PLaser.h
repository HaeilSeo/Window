#pragma once
#include "header.h"
class PLaser : public GameObject {

private:
	float speed;

public:
	PLaser();	//플레이어 레이져 생성자
	PLaser(float x, float y);
	virtual ~PLaser();	//플레이어 레이져 소멸자
	
	virtual void init(); //플레이어 레이져 초기화 정보 
	virtual void update();
};