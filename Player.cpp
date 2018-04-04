#include"Player.h"
Player::Player():GameObject(245,550,"Player",0){
	
}

Player::~Player() {

}

void Player::init() {
	using namespace std;
	////////�÷��̾� �׸� �ε�/////////
//	cout << "                                                              �÷��̾� init" << endl;
	
	DDS_FILE* dds = readDDS("dds/player.dds");
	
	float x = dds->header.dwWidth * 0.5;
	float y = dds->header.dwHeight * 0.5;

	setAnchor(x, y);
	setDDS(dds);
	////////////�÷��̾� ����////////////
	speed = 100;  //1�ʿ� 100�ȼ� �̵�

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


	////////������ �߻� ��� �߰�//////////
	if (GetKey(VK_SPACE)) {
		using namespace std;
		//cout << "                                                              �÷��̾� ������ �߻�" << endl;
		//(1) �÷��̾� ������ Ŭ����
		//(2) �÷��̾� ������ ��ü���� <== Ŭ��������
		
		//PLaser* o = new PLaser;
		
		//������ ��ġ �����ϱ�//////////////
		//(1) ���� �÷��̾� ��ġ ���ϱ�
		float x = getPx();		//�÷��̾� ��ġ
		float y = getPy()-65;

		//(2) �÷��̾� ��ġ�� ���� ������ ��ġ �����ϱ�
	

		//o->setXY(x, y);
		
		//(3) ��ü Ǯ�� �߰�
		//addGameObj(o);
		
		setKeyCode(VK_SPACE);
		addGameObj(new PLaser(getPx(),getPy()));
		
	}
	else
	{
		setKeyCode(NULL);
	}
}
