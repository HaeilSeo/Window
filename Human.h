#ifndef __HUMAN_H__
#define __HUMAN_H__
#include"LivesInterface.h"

class Human : public LivesInterface {
public:
	enum Race{ WHITE = 0, BLACK, ASIAN };

protected:
	//인종
	Race race;

	//국가명
	const char* country;

public:

	Human(LivesInterface::Origin origin, Race race, const char* name, const char* country);

	virtual ~Human();

	Race getRace();

	const char* getCountry();

	void setCountry(const char* country);

	virtual void printToConsole();

	//생물 종에 대한 순수 가상함수 구현
	virtual const char* getSpeciesString();
};
#endif
