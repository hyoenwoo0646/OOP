#ifndef ENEMY_H_
#define ENEMY_H_

#include <cstring>
#include "Players.h"
#include "Bullet.h"


class Enemy : public GameObject, public Damageable {
	float		hp;
	char		face[100];
	char		faceAttacked[100];
	int			nAnimations;
	Players&	players;
	float		speed = 2.0f / 30;

public:
	Enemy(Renderer& renderer, Players& players, int pos = 50, int hp = 5, const char* face = "(*_*)", const char* faceAttacked = "(>_<)")
		: GameObject(renderer, pos, face), Damageable(1.0f), players(players), nAnimations(0), hp(hp)
	{
		strcpy(this->face, face);
		strcpy(this->faceAttacked, faceAttacked);
	}

	void update()
	{
		auto main = players.getMainCharacter();
		if (!main) return;
		float player_pos = main->getPosition();
		float pos = getPosition();
		if (player_pos < pos) move(-1 * speed);
		else if (player_pos > pos) move(1 * speed);
		else {} // do not move

		players.getDamagedIfAttacked(*this);		

		if (nAnimations == 0) return;
		nAnimations--;
		if (nAnimations == 0) {
			setShape(face);
		}
	}

	bool getDamagedIfAttacked(const GameObject& attacker)
	{
		auto bullet = dynamic_cast<const Bullet *>(&attacker); // it only gets attacked when bullets attack.
		if (!bullet) return false;
		Direction bullet_direction = bullet->getDirection();
		float bullet_pos = bullet->getPosition();
		float pos = getPosition();
		if ((bullet_direction == Direction::Left && pos < bullet_pos && bullet_pos - pos <= 1.0f)
			|| (bullet_direction == Direction::Right && bullet_pos < pos && pos - bullet_pos <= 1.0f)
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
