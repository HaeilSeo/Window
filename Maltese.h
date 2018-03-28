#ifndef __MALTESE_H__
#define __MALTESE_H__

#include"Dog.h"

class Maltese : public Dog {
public:

	Maltese(const char* name);

	virtual ~Maltese();

	virtual void printToConsole();

	virtual const char* getSpeciesString();
};

#endif
