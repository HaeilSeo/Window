#ifndef __ROSE_H__
#define __ROSE_H__

#include"LivesInterface.h"

#define ROSE_COLOR_RED 1
#define ROSE_COLOR_YELLOW 2

class Rose : public LivesInterface {
protected:
	// ������ ����
	int petal = 4;
	// ���� ����
	int color = ROSE_COLOR_RED;

public:

	Rose(int petal, int color);

	virtual ~Rose();

	int getPetal();

	int getColor();

	virtual void printToConsole();

	//�������� ���� ���� �����Լ� ����
	virtual const char* getSpeciesString();

};
#endif
