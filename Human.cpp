#include"Human.h"
#include<cstdio>
#include<string.h>


Human::Human(LivesInterface::Origin origin, Race race, const char* name, const char* country):LivesInterface(origin,name) {
	this->race = race;
	this->country = country;
	
}

Human::~Human() {

	delete this->country;
}

Human::Race Human::getRace() {
	return this->race;
}

const char* Human::getCountry() {
	return this->country;
}

void::Human::setCountry(const char* country) {
	this->country = country;
}

void::Human::printToConsole() {
	LivesInterface::printToConsole();
	using namespace std;
	cout << "국가명: " << this->country << endl;
	cout << "race: " << this->race << endl << endl;
}

const char* Human::getSpeciesString() {
	return "사람";
}