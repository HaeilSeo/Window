#include"Player.h"
Player::Player():GameObject(245,550,"Player",0){
	
}

Player::~Player() {

}

void Player::init() {
	using namespace std;
	////////플레이어 그림 로드/////////
//	cout << "                                                              플레이어 init" << endl;
	
	DDS_FILE* dds = readDDS("dds/player.dds");
	
	float x = dds->header.dwWidth * 0.5;
	float y = dds->header.dwHeight * 0.5;

	setAnchor(x, y);
	setDDS(dds);
	////////////플레이어 변수////////////
	speed = 100;  //1초에 100픽셀 이동

}

void Player::update() {
	float dist = getDeltaTime();
	dist = speed * getDeltaTime();
	if (GetKey(VK_LEFT)) {
		translate(-dist, 0);
		//float x = getPx() - dist;
		//float y = getPy();
		//setXY(x, y);
	}
	if (GetKey(VK_RIGHT)) {
		translate(dist, 0);
	}
	if (GetKey(VK_UP)) {
		translate(0, -dist);
	}
	if (GetKey(VK_DOWN)) {
		translate(0, dist);
	}


	////////레이저 발사 기능 추가//////////
	if (GetKey(VK_SPACE)) {
		using namespace std;
		//cout << "                                                              플레이어 레이저 발사" << endl;
		//(1) 플레이어 레이저 클래스
		//(2) 플레이어 레이저 객체생성 <== 클래스에서
		
		//PLaser* o = new PLaser;
		
		//레이저 위치 변경하기//////////////
		//(1) 현재 플레이어 위치 구하기
		float x = getPx();		//플레이어 위치
		float y = getPy()-65;

		//(2) 플레이어 위치에 따라서 레이저 위치 변경하기
	

		//o->setXY(x, y);
		
		//(3) 객체 풀에 추가
		//addGameObj(o);
		
		setKeyCode(VK_SPACE);
		addGameObj(new PLaser(getPx(),getPy()));
		
	}
	else
	{
		setKeyCode(NULL);
	}
}
