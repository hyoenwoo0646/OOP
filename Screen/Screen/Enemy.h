#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstring>
#include "Player.h"
#include "Bullet.h"


class Enemy : public GameObject, public Damageable {
	float		hp;
	char		face[100];
	char		faceAttacked[100];
	int			nAnimations;
	Player*		target;
	float		speed = 2.0f / 30;

public:
	Enemy(Renderer* renderer, Player* target, int pos = 50, int hp = 5, const char* face = "(*_*)", const char* faceAttacked = "(>_<)")
		: GameObject(renderer, pos, face), Damageable(1.0f), target(target), nAnimations(0), hp(hp)
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
		(void)target->getDamagedIfAttacked(this);

		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			setShape(face);
		}
	}

	bool getDamagedIfAttacked(const GameObject* attacker)
	{
		if (!attacker) return false;
		auto bullet = dynamic_cast<const Bullet*>(attacker); // it only gets attacked when bullets attack.
		if (!bullet) return false;
		int bullet_direction = bullet->getDirection();
		float bullet_pos = bullet->getPosition();
		float pos = getPosition();
		if ((bullet_direction == 1 && pos < bullet_pos && bullet_pos - pos <= 1.0f)
			|| (bullet_direction == -1 && bullet_pos < pos && pos - bullet_pos <= 1.0f)
			|| (int)pos == (int)bullet_pos) {
			hp -= getDamage();
			nAnimations = 30;
			setShape(faceAttacked);
			return true;
		}
		return false;
	}

	bool isAlive() {
		return hp > 0.0f;
	}

	float getHP() { return hp; }
};

#endif
