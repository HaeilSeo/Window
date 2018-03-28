#include"LivesInterface.h"
#include<cstdio>
#include<string.h>


LivesInterface::LivesInterface(Origin origin) {
	this->origin = origin;
	
}

LivesInterface::LivesInterface(Origin origin, const char* name) {
	this->origin = origin;
	this->name = name;
	
}

LivesInterface::~LivesInterface() {
	delete this->name;
}

const char* LivesInterface::getName() {
	return this->name;
}

LivesInterface::Origin LivesInterface::getOrigin() {

	return this->origin;
}

LivesInterface::Position& LivesInterface::getPosition() {
	return this->position;
}

void::LivesInterface::setPosition(LivesInterface::Position position) {
	this->position = position;
}

void::LivesInterface::setPosition(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}

void::LivesInterface::printToConsole() {
	using namespace std;
	cout << "��: "<< this->getSpeciesString() << endl;
	cout << "�̸�: " << this->name << endl;
	cout << "������ġ: "<<this->position.x<<" , "<<this->position.y << endl;
}