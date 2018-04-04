#pragma once
///////�ֻ��� �θ�/////////
//#include"header.h"
#include "DDS.h"
class GameObject {
private:
	const char* name;
	int tag;

	//////���Ӱ�ü�� ��ġ, ȸ��, ũ��- Ʈ������//////
	float px, py;	//��ġ ��ǥ
	float speed;	//�ӵ�
	//////�̹����� ��Ŀ����Ʈ///////
	float ax;
	float ay;
	bool alive;
	//////�̹��� DDS ������////////
	DDS_FILE* dds;
public:
	//���࿡ ���� �����Ͱ� ���ٸ� ������ �Ķ���ͺ��� ä��������
	GameObject(float px, float py, const char* name = "", int tag = 0);	//������
	virtual ~GameObject();															//(����)�Ҹ���

	/////////�̵� �Լ�///////////
	void translate(float x, float y);	//-���� ��ġ���� �̵�

	//����(Getter)+����(Setter)
	const char* getName();
	int getTag();
	float getPx();
	float getPy();
	float getAx();
	float getAy();


	void setName(const char* name);
	void setTag(int tag);
	void setXY(float x, float y);
	void setAnchor(float x, float y);
	void setDDS(DDS_FILE* dds);
	void dead_Alive();
	bool getAlive();
	//�⺻ �޼ҵ�//
	virtual void init();
	virtual void update();
	virtual void render();

	//�浹 üũ�ϱ�//
	virtual bool checkCollision(GameObject* target);


public:
	int keycode;

	void setKeyCode(int keycode)
	{
		this->keycode = keycode;
	}

	int getKeyCode()
	{
		return this->keycode;

	}
};