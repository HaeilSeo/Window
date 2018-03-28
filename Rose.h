#ifndef __ROSE_H__
#define __ROSE_H__

#include"LivesInterface.h"

#define ROSE_COLOR_RED 1
#define ROSE_COLOR_YELLOW 2

class Rose : public LivesInterface {
protected:
	// 꽃잎의 갯수
	int petal = 4;
	// 꽃의 색상
	int color = ROSE_COLOR_RED;

public:

	Rose(int petal, int color);

	virtual ~Rose();

	int getPetal();

	int getColor();

	virtual void printToConsole();

	//생물종에 대한 순수 가상함수 구현
	virtual const char* getSpeciesString();

};
#endif
