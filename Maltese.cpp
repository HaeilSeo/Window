#include"Maltese.h"
#include<cstdio>


Maltese::Maltese(const char* name) : Dog(LivesInterface::Origin::EVERYWHERE, name) {
	setColor(FUR_COLOR_WHITE);
}

Maltese::~Maltese() {}

void Maltese::printToConsole() {
	using namespace std;
	cout << "우리 귀여운 말티즈~" << endl;
	Dog::printToConsole();
	cout << endl;
}


const char* Maltese::getSpeciesString() {
	return "말티즈";
}
