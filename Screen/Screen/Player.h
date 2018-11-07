#ifndef PLAYER_H_
#define PLAYER_H_

#include <ctime>
#include "GameObject.h"

class Player : public GameObject, public Damageable {
	float	hp;
	
public:
	Player(Renderer& renderer, int hp = 10, int pos = 20, const char *face= "(-_-)")
		: GameObject(renderer, pos, face), Damageable(2.0f/30), hp(hp)
	{}

	bool isAlive() { return hp > 0.0f; }

	bool getDamagedIfAttacked(const GameObject& attacker)
	{
		if (fabs(getPosition() - attacker.getPosition()) > 2.0f) return false;
		hp -= getDamage();
		return true;
	}

	virtual void displayStat()
	{
		printf("[pos: %2.1f hp:%2.1f] ", getPosition(), hp);
	}
};


class Ship : public Player {
	Direction	direction;
	char		faceLeft[100];
	char		faceRight[100];
public:
	Ship(Renderer& renderer, int hp = 10, int pos = 20, const char* shape="|____|", Direction direction = Direction::Left) : Player(renderer, hp, pos, shape), direction(direction)
	{
		setDirectionalFace(shape, shape);
	}

	void setDirectionalFace(const char* left, const char* right)
	{
		strcpy(faceLeft, left);
		strcpy(faceRight, right);
	}

	void toggleDirection() 
	{
		direction = (direction == Direction::Left) ? Direction::Right : Direction::Left;
	}

	Direction getDirection() const { return direction; }
	
	void draw() 
	{
		drawToRenderer( direction == Direction::Left ? faceLeft : faceRight, getPosition());
	}
};

class Boat : public Ship {

public:
	Boat(Renderer& renderer, int hp = 5, int pos = 20, Direction direction=Direction::Left) : Ship(renderer, hp, pos, "+", direction) {}

};

class MainShip : public Ship {

public:
	MainShip(Renderer& renderer, int hp = 10, int pos = 20, const char* shape="-____|", Direction direction=Direction::Left) : Ship(renderer, hp, pos, shape, direction) {
		setDirectionalFace("-____|", "|____-");
	}
};

class BlinkablePlayer : public Player {
	int		nBlinks;
public:
	BlinkablePlayer(Renderer& renderer, int hp = 10, int pos = 20 )
		: Player(renderer, hp, pos), nBlinks(0)
	{}

	void update()
	{
		if (nBlinks > 0) nBlinks--;
	}

	bool isBlinking() { return nBlinks > 0; }

	bool getDamagedIfAttacked(const GameObject& attacker)
	{

		if (Player::getDamagedIfAttacked(attacker) == false) return false;
		nBlinks = 2;
		return true;
	}

	void displayStat()
	{
		Player::displayStat();
		printf("n_blinks(%2d)", nBlinks);
	}

	void draw()
	{
		if (isBlinking() == false)
			Player::draw();
		else drawToRenderer(rand() % 2 ? getShape() : " ", getPosition());
	}
};

#endif