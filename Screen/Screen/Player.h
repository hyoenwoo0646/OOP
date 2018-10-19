#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject {
	float	hp;
	int		nBlinks;
	float	damageRatio;
	bool	isDamanaged;
public:
	Player(int hp = 10, int pos = 20, const char *face = "(-_-)")
		: GameObject(pos, face), hp(hp), nBlinks(0), damageRatio(2.0f / 30)
	{}

	void update()
	{
		if (nBlinks > 0) nBlinks--;
	}

	bool isBlinking() { return nBlinks > 0; }

	bool isAlive() { return hp > 0.0f; }

	void getDamanagedIfIntruded(float enemy_pos)
	{
		if (fabs(getPosition() - enemy_pos) > 2.0f) return;
		hp -= damageRatio;
		nBlinks = 2;
	}

	void displayStat()
	{
		printf("pos(%2.1f) hp(%2.1f), n_blinks(%2d)", getPosition(), hp, nBlinks);
	}
};

#endif

