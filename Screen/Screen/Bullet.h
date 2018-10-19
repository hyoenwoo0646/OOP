#ifndef BULLET_H_
#define BULLET_H_

#include <cstring>
#include "GameObject.h"

class Bullet : public GameObject {
public:
	Bullet(Renderer* renderer, int player_pos = -1, const char* shape = ">") : GameObject(renderer, player_pos, shape) {}

	int getDirection() const 
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
