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
		cout << "�Ƹ��ٿ� �״뿡�� �������� ���� ��̸�" << endl;
	}
	else if (this->color == ROSE_COLOR_YELLOW) {
		cout << "����ϴ� ��ſ��� �Ϳ��� �����̸�" << endl;
	}

	LivesInterface::printToConsole();
	cout << "������ ����: " << this->petal << endl<<endl;
}

const char* Rose::getSpeciesString() {
	return "���";
}