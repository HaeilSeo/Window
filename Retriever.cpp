#include"Retriever.h"
#include<cstdio>


Retriever::Retriever(const char* name) :Dog(LivesInterface::EVERYWHERE, name) {
	setColor(FUR_COLOR_GOLDEN);
}

Retriever::~Retriever() {}

void Retriever::printToConsole() {
	using namespace std;
	cout << "리트리버는 착하고 영리합니다" << endl;
	Dog::printToConsole();
	cout << endl;
}

const char* Retriever::getSpeciesString() {
	return "리트리버";
}