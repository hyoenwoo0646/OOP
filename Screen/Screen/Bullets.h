#ifndef BULLETS_H_
#define BULLETS_H_

#include "Renderer.h"
#include "Bullet.h"
#include "Players.h"
#include "Enemies.h"
#include <algorithm>
#include <vector>

class Bullets {
	Renderer&	renderer;
	Players&	players;
	Enemies&	enemies;
	vector<Bullet*> container;
	int			n_remaining_cool_time;
	const unsigned int	max_bullets;
	int			n_penetrable_cool_time;

public:
	Bullets(Players& players, Enemies& enemies)
		: max_bullets(10), renderer(Renderer::getInstance()), players(players), enemies(enemies), 
		  n_remaining_cool_time(0), // the number of frames that bullet weapons are loaded.
		  n_penetrable_cool_time(0) // the number of frames that PenetrableCannonball weapon is ready to use
	{}

	// this function assumes the given bullet is allocated in advance.
	// if we cannot insert the bullet to the container, we need to free them since there is no way the caller knows
	// that the bullet is not inserted.
	// if we want to make the caller know the situation when the bullet cannot be inserted,
	// we may use return value to indicate whether the bullet is inserted into the container.
	// my solution is to remove the bullet just in case we cannot insert into the container.
	void add(Bullet* bullet)
	{
		if (!bullet) return;

		// examine whether the container cannot accept any incoming bullet waiting until bullet reloading is ready.
		if (n_remaining_cool_time > 0) {
			n_remaining_cool_time--;
			delete bullet;
			return;
		}

		// examine whether the container is occupied by all bullet weapons. if so, reject newly incoming bullet.
		if (container.size() >= max_bullets) {
			if (n_remaining_cool_time == 0) {
				n_remaining_cool_time = 30 * 2;
			}
			delete bullet;
			return;
		}

		// otherwise, simply insert the new bullet to the container.
		container.push_back(bullet);
	}

	// this function fires one bullet per player, including mainship and boat.
	// To recognize all players, we need a help from the player manager who maintains a player list.
	// to minimize any possible side-effects caused by allowing to access the players' container,
	// we force the playerContainer const - i.e., const vector<Player*>& playerContainer.
	void fire()
	{
		auto playerContainer = players.getContainer();
		for (auto player : playerContainer) fire(*player);
	}

	void fire(const Ship& player)
	{
		float player_pos = player.getPosition();
		// if the player's position is out of range, simply ignore this fire request.
		if (renderer.checkRange(player_pos) == false) return;

		// examine whether PenetrableCannonball is ready.
		if (n_penetrable_cool_time == 0) {
			// if so, fire "PenetrableCannonball", while targetting the player.
			n_penetrable_cool_time = 5 * 30;
			add(new PenetrableCannonball(player_pos, player.getDirection()));
		} else {
			// otherwise, fire an ordinary Cannonball.
			add(new Cannonball(player_pos, player.getDirection()));
		}
	}

	void update()
	{
		if (n_remaining_cool_time > 0)
			n_remaining_cool_time--;

		for (auto bullet : container) bullet->update();

		// examine whether bullet is not alive. if so, free it and remove from the container.
		container.erase(
			remove_if(container.begin(), container.end(), 
				[](Bullet* bullet) { 
					if (bullet->isAlive() == false) { 
						delete bullet; 
						return true; 
					}
					return false; 
				}), 
			container.end()
		);

		if (n_penetrable_cool_time > 0) n_penetrable_cool_time--;
		
		for (auto it = container.begin(); it != container.end();)
		{
			// if a bullet is hit by an enemy, execute bullet hit operation lowering its damagePower
			// and remove it from the container if it is one of ordinary cannonballs.
			if (enemies.isShoted(*(*it)) == true) {
				(*it)->hit();
				if (dynamic_cast<PenetrableCannonball*>(*it)) {
					it++;
				}
				else {
					delete *it;
					it = container.erase(it);
				}
			}
			else {
				it++;
			}
		}

		Borland::gotoxy(0, 3); printf("# of bullets = %2d ", container.size());		
		printf("%5s %20s\n", n_remaining_cool_time == 0 ? "ready" : " ", n_penetrable_cool_time == 0 ? "penCannonball ready" : " ");
		Borland::gotoxy(0, 4); for (auto bullet : container) printf("%2.1f ", bullet->getDamagePower());
	}

	void draw()
	{
		for (auto bullet : container) bullet->draw();
	}
};

#endif
