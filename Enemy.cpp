#include"Enemy.h"
Enemy::Enemy() :GameObject(244,100,"enemy",1) {

	
}
	
Enemy::~Enemy() {


}

void Enemy::init() {
	DDS_FILE* dds = readDDS("dds/enemy2.dds");
	
	float x = dds->header.dwWidth*0.5;
	float y = dds->header.dwHeight*0.5;


	setAnchor(x, y);
	setDDS(dds);
	fireTime = 0;
	fireRate = 1;
	speed = 150;
}

void Enemy::update() {
	float dist;
	float x = getPx();	//���ʹ��� ���� x-�� ��ǥ�� ���Ѵ�.
	float y = getPy();	//���ʹ��� ���� y-�� ��ǥ�� ���Ѵ�.
	if (getPx() > 425) {
		speed = -speed;
	}
	else if (getPx() < 45) {
		speed = -speed;
	}
	dist = 0.01*speed;
	translate(dist, 0);
	///////////������ �߻� ���///////////////
	/*
	fireTime = fireTime + getDeltaTime();	//�߻� �ð��� ���ϱ� ���ؼ� �ð��� ��� �����Ѵ�.
	if (fireTime >= fireRate) {

		addGameObj(new ELaser(x, y+ 65));
		fireTime = 0;
	}
	*/
}

