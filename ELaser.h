#pragma once
#include "header.h"

class ELaser :public GameObject {
private:
	float speed;
	
public:
	ELaser(float px,float py);
	virtual ~ELaser();	//��ü ���� ��ġ�� �����ڷ�.. �޾ƿ� ���� ����

	virtual void init();
	virtual void update();
};