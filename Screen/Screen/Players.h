#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <iostream>
#include <cmath>
#include "Renderer.h"
#include "Player.h"

#include <vector>
#include <algorithm>

using namespace std;

class Players {
	Renderer&			renderer;
	int					n_launch_cool_time;
	vector<Ship*>		container;

public:
	Players(Renderer& renderer) : renderer(renderer), n_launch_cool_time(5*30)
	{
		container.push_back(new MainShip(renderer));
	}

	const vector<Ship*>&	getContainer() { return container; }

	Ship* getMainCharacter()
	{
		if (container.size() == 0) return nullptr;
		return dynamic_cast<Ship *>(container[0]);
	}

	void move(int pos)
	{
		auto main = getMainCharacter();
		if (!main) return;
		auto dir = main->getDirection();

		for (auto ship : container) {
			if (dir == Direction::Left) {
				if (pos > 0) ship->toggleDirection();
			}
			else {
				if (pos < 0) ship->toggleDirection();
			}
			ship->move(pos);
		}
	}
		
	void update()
	{
		if (n_launch_cool_time == 0) {
			auto main = dynamic_cast<Ship *>(getMainCharacter());
			if (main) {
				// add the boat as the way the problem requires.
				int main_pos = (float)main->getPosition();
				Direction dir = main->getDirection();
				int probabilisticValue = rand() % 100;
				int target_pos = main_pos;
				if (dir == Direction::Left) {
					target_pos = (probabilisticValue < 20) ?
						target_pos + (7 + rand() % 4) : target_pos - (1 + rand() % 4);
				} else {
					target_pos = (probabilisticValue < 20) ?
						target_pos - (1 + rand() % 4) : target_pos + (7 + rand() % 4);
				}
				container.push_back(new Boat(renderer, 5, target_pos, dir));
				n_launch_cool_time = 5 * 30;
			}
		} else {
			n_launch_cool_time--;
		}

		for (auto player : container) player->update();
		container.erase(remove_if(container.begin(), container.end(), 
				[](Player *player) { if (player->isAlive() == false) { delete player; return true; } return false; }), 
			container.end());

		for (auto player : container) if (dynamic_cast<MainShip *>(player)) return;

		container.erase(remove_if(container.begin(), container.end(), 
				[](Player* player) { delete player; return true; }), 
			container.end());
	}

	void draw()
	{
		for (auto player : container) player->draw();
		Borland::gotoxy(0, 1); printf("player "); for (auto player : container) player->displayStat(); printf("\n");
	}

	void getDamagedIfAttacked(const GameObject& attacker)
	{
		for (auto player : container) player->getDamagedIfAttacked(attacker);
	}
};

#endif

