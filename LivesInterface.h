#ifndef __LIVES_INTERFACE_H__
#define __LIVES_INTERFACE_H__
#include<iostream>
class LivesInterface {
public:

	enum Origin { ASIA=0,AFRICA,EUROPE,AMERICA,EVERYWHERE,UNKNOWN };

	struct Position {
		float x;
		float y;
	};
protected:
	Position position;
	Origin origin;
	const char* name;
public:
	LivesInterface(Origin origin);

	LivesInterface(Origin origin, const char* name);	//Ŭ������ ������

	//�Ҹ��ڸ� �����Ѵ�.
	virtual ~LivesInterface();

	//�̸�
	const char* getName();

	Origin getOrigin();


	//���� ��ġ�� Reference ���·� ��ȯ�Ѵ�.
	Position& getPosition();

	void setPosition(Position position);

	void setPosition(float x, float y);

	virtual void printToConsole();

	//�� ������ ��� ���� �����ִ����� �����ؾ� �ϴ� ���������Լ�
	virtual const char* getSpeciesString() = 0;
};

#endif