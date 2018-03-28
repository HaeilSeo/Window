#ifndef __RETRIEVER_H__
#define __RETRIEVER_H__
#include"Dog.h"

class Retriever : public Dog {
public:

	Retriever(const char* name);
	virtual ~Retriever();

	virtual void printToConsole();

	virtual const char* getSpeciesString();

};

#endif
