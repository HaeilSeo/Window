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
	float x = getPx();	//에너미의 현재 x-축 좌표를 구한다.
	float y = getPy();	//에너미의 현재 y-축 좌표를 구한다.
	if (getPx() > 425) {
		speed = -speed;
	}
	else if (getPx() < 45) {
		speed = -speed;
	}
	dist = 0.01*speed;
	translate(dist, 0);
	///////////레이져 발사 기능///////////////
	/*
	fireTime = fireTime + getDeltaTime();	//발사 시간을 구하기 위해서 시간을 계속 측정한다.
	if (fireTime >= fireRate) {

		addGameObj(new ELaser(x, y+ 65));
		fireTime = 0;
	}
	*/
}

