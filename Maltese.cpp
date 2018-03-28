#include"Maltese.h"
#include<cstdio>


Maltese::Maltese(const char* name) : Dog(LivesInterface::Origin::EVERYWHERE, name) {
	setColor(FUR_COLOR_WHITE);
}

Maltese::~Maltese() {}

void Maltese::printToConsole() {
	using namespace std;
	cout << "�츮 �Ϳ��� ��Ƽ��~" << endl;
	Dog::printToConsole();
	cout << endl;
}


const char* Maltese::getSpeciesString() {
	return "��Ƽ��";
}
