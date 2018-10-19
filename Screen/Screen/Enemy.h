#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstring>
#include "Player.h"


class Enemy : public GameObject {
	float		hp;
	char		face[100];
	char		faceAttacked[100];
	int			nAnimations;
	Player*		target;
	float		speed = 2.0f / 30;

public:
	Enemy(Player* target, int pos = 50, int hp = 5, const char* face = "(*_*)", const char* faceAttacked = "(>_<)")
		: GameObject(pos, face), target(target), nAnimations(0), hp(hp)
	{
		strcpy(this->face, face);
		strcpy(this->faceAttacked, faceAttacked);
	}

	void update()
	{
		if (!target) return;
		float player_pos = target->getPosition();
		float pos = getPosition();
		if (player_pos < pos) move(-1 * speed);
		else if (player_pos > pos) move(1 * speed);
		else {} // do not move

				// attack if in range
		target->getDamanagedIfIntruded(pos);

		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			setShape(face);
		}
	}
	void OnHit()
	{
		hp -= 1.0f;
		nAnimations = 30;
		setShape(faceAttacked);
	}

	bool isAlive() {
		return hp > 0.0f;
	}

	float getHP() { return hp; }
};

#endif
