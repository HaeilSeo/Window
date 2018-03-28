#include"Retriever.h"
#include<cstdio>


Retriever::Retriever(const char* name) :Dog(LivesInterface::EVERYWHERE, name) {
	setColor(FUR_COLOR_GOLDEN);
}

Retriever::~Retriever() {}

void Retriever::printToConsole() {
	using namespace std;
	cout << "��Ʈ������ ���ϰ� �����մϴ�" << endl;
	Dog::printToConsole();
	cout << endl;
}

const char* Retriever::getSpeciesString() {
	return "��Ʈ����";
}