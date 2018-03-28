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

	LivesInterface(Origin origin, const char* name);	//클래스의 생성자

	//소멸자를 정의한다.
	virtual ~LivesInterface();

	//이름
	const char* getName();

	Origin getOrigin();


	//현재 위치를 Reference 형태로 반환한다.
	Position& getPosition();

	void setPosition(Position position);

	void setPosition(float x, float y);

	virtual void printToConsole();

	//이 생물이 어떤한 종에 속해있는지를 리턴해야 하는 순수가상함수
	virtual const char* getSpeciesString() = 0;
};

#endif