#include"ELaser.h"

ELaser::ELaser(float px, float py) :GameObject( px, py, "enemylaser", 1) {

}

ELaser::~ELaser() {


}

void ELaser::init() {
	DDS_FILE* dds = readDDS("dds/laserE2.dds");

	float x = dds->header.dwWidth*0.5;
	float y = dds->header.dwHeight*0.5;
	
	setAnchor(x, y);
	setDDS(dds);
	speed = 400;
	
}

void ELaser::update() {
	
	float dist = getDeltaTime() * speed;
	translate(0, dist);
}