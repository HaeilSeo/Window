#pragma once
///////최상위 부모/////////
//#include"header.h"
#include "DDS.h"
class GameObject {
private:
	const char* name;
	int tag;

	//////게임객체의 위치, 회전, 크기- 트랜스폼//////
	float px, py;	//위치 좌표
	float speed;	//속도
	//////이미지의 앵커포인트///////
	float ax;
	float ay;
	bool alive;
	//////이미지 DDS 포인터////////
	DDS_FILE* dds;
public:
	//만약에 넣을 데이터가 없다면 오른쪽 파라미터부터 채워나가자
	GameObject(float px, float py, const char* name = "", int tag = 0);	//생성자
	virtual ~GameObject();															//(가상)소멸자

	/////////이동 함수///////////
	void translate(float x, float y);	//-현재 위치에서 이동

	//게터(Getter)+세터(Setter)
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
	//기본 메소드//
	virtual void init();
	virtual void update();
	virtual void render();

	//충돌 체크하기//
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