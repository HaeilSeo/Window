#include"Dog.h"
#include<cstdio>
#include<cstring>


Dog::Dog(LivesInterface::Origin origin, const char* name) :LivesInterface(origin, name) {

	ownerName = new char[100];
}

Dog::~Dog() {
	delete[] ownerName;
}

void Dog::setColor(int furColor) {

	this->furColor = furColor;
}

void Dog::setOwnerName(const char* ownerName) {

	strcpy_s(this->ownerName, 100, ownerName);
}