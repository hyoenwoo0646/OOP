#ifndef  ENEMIES_H_
#define ENEMIES_H_

#include "Enemy.h"
#include "Bullet.h"
#include "Players.h"
#include <algorithm>
#include <vector>

using namespace std;

class Enemies {
	Renderer&			renderer;
	Players&			players;
	vector<Enemy*>		container;

	int n_killed;
	int n_remainings_for_respawn;
	const unsigned int max_enemies;

public:
	Enemies(Renderer& renderer, Players& players)
		: renderer(renderer), n_killed(0), n_remainings_for_respawn(30), players(players), max_enemies(5)
	{	container.push_back(new Enemy(renderer, players, rand() % renderer.getScreenLength())); }

	int getNumberOfKilled() { return n_killed; }

	void update()
	{
		// spawn enemies periodically.
		if (n_remainings_for_respawn <= 0) {
			// reset the timer for the next enemy spawning
			if (container.size() < max_enemies)
				container.push_back(new Enemy(renderer, players, rand() % renderer.getScreenLength()));
			n_remainings_for_respawn = 30;
		} else {
			n_remainings_for_respawn--;
		}

		// update all enemies
		for (auto enemy : container) enemy->update();
		
		int size = container.size();
		container.erase(remove_if(container.begin(), container.end(), 
			[](Enemy* enemy) { 
				if (enemy->isAlive() == false) { 
					delete enemy; // you need to free the dynamically allocated enemies.
					return true;
				}
				return false; 
			}), container.end());
		n_killed += size - container.size();
	}

	void draw()
	{
		for (auto enemy : container) enemy->draw();
		Borland::gotoxy(0, 2); printf("# of enemies = %2d,  ", container.size());
		for (auto enemy : container) printf("%2.1f %2.1f  ", enemy->getPosition(), enemy->getHP());
	}

	Enemy* findClosest(float pos)
	{
		Enemy* closest = nullptr;
		float dist = 0.0f;
		if (renderer.checkRange(pos) == false) return closest;
		for (auto enemy : container) {
			float enemy_pos = enemy->getPosition();
			if (renderer.checkRange(enemy_pos) == false) continue;
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

	bool isShoted(Bullet& bullet)
	{
		auto enemy = findClosest(bullet.getPosition());
		if (!enemy) return false;
		return enemy->getDamagedIfAttacked(bullet);
	}
};


#endif

