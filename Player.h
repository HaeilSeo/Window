#pragma once
#include "header.h"

class Player : public GameObject {
private:
	//�÷��̾� ����
	float speed;
public:
	Player();
	virtual ~Player();

	virtual void init();
	virtual void update();

};