#ifndef __HUMAN_H__
#define __HUMAN_H__
#include"LivesInterface.h"

class Human : public LivesInterface {
public:
	enum Race{ WHITE = 0, BLACK, ASIAN };

protected:
	//����
	Race race;

	//������
	const char* country;

public:

	Human(LivesInterface::Origin origin, Race race, const char* name, const char* country);

	virtual ~Human();

	Race getRace();

	const char* getCountry();

	void setCountry(const char* country);

	virtual void printToConsole();

	//���� ���� ���� ���� �����Լ� ����
	virtual const char* getSpeciesString();
};
#endif
