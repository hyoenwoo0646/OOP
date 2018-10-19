#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <iostream>
#include <cmath>
#include "Renderer.h"
#include "Player.h"
#include "Container.h"

class Players {
	Renderer*			renderer;
	Player*				main;
	Container<Player*>	container;

public:
	Players(Renderer* renderer) : container(1), renderer(renderer)
	{
		container.add(new BlinkablePlayer(renderer));
	}

	Player* getMainCharacter()
	{
		if (container.count() == 0) return nullptr;
		for (int i = 0; i < container.capacity(); i++) {
			if (container[i] != nullptr) return container[i];
		}
		return nullptr;
	}

	void update()
	{
		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			container[i]->update();
		}

		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			if (container[i]->isAlive() == false) container.remove(i);
		}
	}

	void draw()
	{
		for (int i = 0; i < container.capacity(); i++) {
			if (!container[i]) continue;
			container[i]->draw();
		}
		Borland::gotoxy(0, 1); printf("player "); getMainCharacter()->displayStat();
	}
};

#endif

