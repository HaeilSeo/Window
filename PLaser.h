#pragma once
#include "header.h"
class PLaser : public GameObject {

private:
	float speed;

public:
	PLaser();	//�÷��̾� ������ ������
	PLaser(float x, float y);
	virtual ~PLaser();	//�÷��̾� ������ �Ҹ���
	
	virtual void init(); //�÷��̾� ������ �ʱ�ȭ ���� 
	virtual void update();
};