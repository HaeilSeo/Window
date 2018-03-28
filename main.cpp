#include"LivesInterface.h"
#include"Human.h"
#include"Dog.h"
#include"Retriever.h"
#include"Maltese.h"
#include"Rose.h"
#include<cstdio>
#include<cstring>

int main() {

	LivesInterface* lives[7];

	Human* james = new Human(LivesInterface::Origin::EUROPE, Human::Race::WHITE, "James", "England");
	Human* ashely = new Human(LivesInterface::Origin::AMERICA, Human::Race::BLACK, "Ashely", "USA");
	Human* cheolsoo = new Human(LivesInterface::Origin::ASIA, Human::Race::ASIAN, "Cheolsoo", "Korea");

	james->setPosition(100.0f, 200.0f);
	ashely->setPosition(200.0f, -20.f);
	cheolsoo->setPosition(400.0f, 50.0f);

	LivesInterface::Position dogPosition;
	dogPosition.x = 912.0f;
	dogPosition.y = 606.0f;

	Dog* maltese = new Maltese("Digger");
	maltese->setOwnerName(cheolsoo->getName());
	maltese->setPosition(dogPosition);

	Dog* retriever = new Retriever("¸Û¸ÛÀÌ");
	retriever->setOwnerName(cheolsoo->getName());
	retriever->setPosition(dogPosition);

	Rose* redRose = new Rose(20, ROSE_COLOR_RED);
	Rose* yellowRose = new Rose(14, ROSE_COLOR_YELLOW);

	redRose->getPosition().x = 200.0f;
	redRose->getPosition().y = 212.0f;
	yellowRose->getPosition().x = -1.0f;
	yellowRose->getPosition().y = -2.0f;


	lives[0] = james;
	lives[1] = ashely;
	lives[2] = cheolsoo;
	lives[3] = maltese;
	lives[4] = retriever;
	lives[5] = redRose;
	lives[6] = yellowRose;

	for (int i = 0; i < 7; i++) {

		lives[i]->printToConsole();
	}

	fgetc(stdin);
	return 0;
}