#include"Rose.h"
#include<cstdio>

Rose::Rose(int petal, int color) :LivesInterface(LivesInterface::Origin::EUROPE, getSpeciesString()) {
	this->petal = petal;
	this->color = color;
}
Rose::~Rose() {}

int Rose::getPetal() {
	return this->petal;
}

int Rose::getColor() {
	return this->color;
}

void Rose::printToConsole() {
	using namespace std;
	if (this->color == ROSE_COLOR_RED) {
		cout << "아름다운 그대에게 정열적인 빨간 장미를" << endl;
	}
	else if (this->color == ROSE_COLOR_YELLOW) {
		cout << "사랑하는 당신에게 귀여운 노란장미를" << endl;
	}

	LivesInterface::printToConsole();
	cout << "꽃잎의 갯수: " << this->petal << endl<<endl;
}

const char* Rose::getSpeciesString() {
	return "장미";
}