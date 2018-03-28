#ifndef __DOG_H__
#define __DOG_H__
#include"LivesInterface.h"

#define FUR_COLOR_WHITE 0xffffff
#define FUR_COLOR_BLACK 0x000000
#define FUR_COLOR_GOLDEN 0x9b8509


class Dog : public LivesInterface {
protected:
	int furColor = FUR_COLOR_WHITE;

	char* ownerName;

	void setColor(int furColor);

public:

	Dog(LivesInterface::Origin origin, const char* name);

	virtual ~Dog();

	void setOwnerName(const char* ownerName);

};


#endif