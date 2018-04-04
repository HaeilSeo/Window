#include"PLaser.h"
PLaser::PLaser() :GameObject(240, 500, "player laser", 0) {
	

}
PLaser::PLaser(float x, float y) : GameObject(x, y, "player laser", 0) {


}
PLaser::~PLaser() {


}

void PLaser::init() {
	DDS_FILE* dds = readDDS("dds/laserP.dds");

	float x = dds->header.dwWidth* 0.5;
	float y = dds->header.dwHeight* 0.5;

	setAnchor(x, y);
	setDDS(dds);
	/////레이져가 날라가는 속도
	speed = 1000;
	
}

void PLaser::update() {
	
	float x = getPx();
	float y = getPy();
	float dist = getDeltaTime() * speed;
	translate(0, -dist);
	
	if (y < 0)
	{
		dead_Alive();  // 상태만 바꿔주는거
	}
}