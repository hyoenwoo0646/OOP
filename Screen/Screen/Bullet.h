#ifndef BULLET_H_
#define BULLET_H_

#include <cstring>
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet(int player_pos = -1, const char* shape = ">") : GameObject(player_pos, shape) {}

	int getDirection()
	{
		return strcmp(getShape(), ">") == 0 ? 1 : -1;
	}

	void update()
	{
		if (isAlive() == false) return;
		if (strcmp(getShape(), ">") == 0) move(1.0f);
		else if (strcmp(getShape(), "<") == 0) move(-1.0f);
	}
	bool isAlive() { return getPosition() != -1.0f; }
};

#endif
