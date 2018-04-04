#pragma once
#include "header.h"

class Player : public GameObject {
private:
	//플레이어 변수
	float speed;
public:
	Player();
	virtual ~Player();

	virtual void init();
	virtual void update();

};