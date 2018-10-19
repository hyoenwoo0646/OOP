#ifndef  ENEMIES_H_
#define ENEMIES_H_

#include "Enemy.h"
#include "Bullet.h"
#include "Container.h"

class Enemies {
	Renderer*			renderer;
	Player*				target;
	Container<Enemy*>	container;

	int n_killed;
	int n_remainings_for_respawn;

public:
	Enemies(Renderer* renderer, Player* target)
		: container(5), renderer(renderer), n_killed(0), n_remainings_for_respawn(30), target(target)
	{
		container.add(new Enemy(renderer, target, rand() % renderer->getScreenLength()));
	}

	int getNumberOfKilled() { return n_killed; }

	void update()
	{
		// enemy spawning related code
		if (n_remainings_for_respawn <= 0) {
			// reset the timer for the next enemy spawning
			container.add(new Enemy(renderer, target, rand() % renderer->getScreenLength()));
			n_remainings_for_respawn = 30;
		}
		else
			n_remainings_for_respawn--;

		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			auto item = container[i];
			item->update();
			if (item->isAlive() == false) {
				n_killed++;
				container.remove(i);
			}
		}
	}

	void draw()
	{
		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			container[i]->draw();
		}
		Borland::gotoxy(0, 2); printf("# of enemies = %2d,  ", container.count());
		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			auto item = container[i];
			printf(" [%2d] %2.1f %2.1f   ", i, item->getPosition(), item->getHP());
		}
	}

	Enemy* findClosest(float pos)
	{
		Enemy* closest = nullptr;
		float dist = 0.0f;
		if (renderer->checkRange(pos) == false) return closest;
		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			auto enemy = container[i];
			float enemy_pos = enemy->getPosition();
			if (renderer->checkRange(enemy_pos) == false) continue;
			float current_dist = fabs(pos - enemy_pos);
			if (!closest) {
				dist = current_dist;
				closest = enemy;
				continue;
			}
			// closest != nullptr;
			if (dist > current_dist) {
				dist = current_dist;
				closest = enemy;
			}
		}
		return closest;
	}

	bool isShoted(Bullet* bullet)
	{
		if (!bullet) return false;
		auto enemy = findClosest(bullet->getPosition());
		if (!enemy) return false;
		return enemy->getDamagedIfAttacked(bullet);
	}
};


#endif

