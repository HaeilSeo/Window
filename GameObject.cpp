#include"GameObject.h"

GameObject::GameObject(float px, float py, const char* name, int tag) {
	this->px = px;
	this->py = py;
	this->name = name;
	this->tag = tag;
	
	this->dds = NULL;
	this->alive = true;
}
GameObject::~GameObject() {
	if (dds != NULL) {
		delete dds;
		dds = NULL;
	}

}																

void GameObject::init() {
	/******************************************************
	//DDS �о����/////
	dds = readDDS("dds/player.dds");

	//ȸ�� ��Ű�� ����
	/////�̹����� ������ ��Ŀ(ȸ����ų���� �߽�)��(��) ������/////
	ax = dds->header.dwWidth*0.5;		//�׸��� �������� �߰�
	ay = dds->header.dwHeight*0.5;		//�׸��� �������� �߰�
	********************************************************/
}
void GameObject::update() {
	

}
void GameObject::translate(float x, float y) {
	px = px + x;
	py = py + y;
}
void GameObject::render() {
	if (dds != NULL) {
		//////�̹��� �׸� �׸���///////
		BYTE * data = dds->data;
		for (int y = 0; y < dds->header.dwHeight; y++){
			for (int x = 0; x < dds->header.dwWidth; x++){
				BYTE a = data[3];
				BYTE r = data[2];
				BYTE g = data[1];
				BYTE b = data[0];

				setPixel(px + x-ax, py + y -ay, r, g, b);
				
				data = data + 4;
			}
		}
	}
}

bool GameObject::checkCollision(GameObject* target) {

	return false;
}
void GameObject::dead_Alive() {
	alive = false;
}

bool GameObject::getAlive() {
	return alive;
}

const char* GameObject::getName() {
	return name;
}

int GameObject::getTag() {
	return tag;
}

float GameObject::getPx() {
	return px;
}
float GameObject::getAx() {
	return ax;
}
float GameObject::getAy() {
	return ay;
}

void GameObject::setAnchor(float x, float y) {
	this -> ax = x;
	this -> ay = y;
}

float GameObject::getPy() {
	return py;
}
void GameObject::setDDS(DDS_FILE* dds) {
	this->dds = dds;
}

void GameObject::setName(const char* name) {
	this->name = name;
}

void GameObject::setTag(int tag) {
	this->tag = tag;
}

void GameObject::setXY(float x, float y) {
	this->px = x;
	this->py = y;
}
