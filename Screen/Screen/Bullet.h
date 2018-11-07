#ifndef BULLET_H_
#define BULLET_H_

#include <cstring>
#include "GameObject.h"

class Bullet : public GameObject {
	float damagePower;
public:
	Bullet(Renderer& renderer, int player_pos = -1, const char* shape = ">", float damagePower = 1.0f)
		: GameObject(renderer, player_pos, shape), damagePower(damagePower) {}

	virtual Direction getDirection() const 
	{
		return strcmp(getShape(), ">") == 0 ? Direction::Right : Direction::Left;
	}

	float getDamagePower() const { return damagePower; } // damage power getter 

	void setDamagePower(float damagePower) { this->damagePower = damagePower; } // damage setter

	// by default, after hitting an enemy, it looses all damage power - that is, dead.
	// it may be overwritten by its sub-class such as PenetrableCannonball.
	virtual void hit() { setDamagePower(0.0f); } 

	void update()
	{
		if (isAlive() == false) return;

		// movement is decided by its shape.
		if (strcmp(getShape(), ">") == 0) move(1.0f);
		else if (strcmp(getShape(), "<") == 0) move(-1.0f);
	}

	bool isAlive() 
	{ 
		if (damagePower <= 0.0f) return false; // if a bullet has no damage power, it will be considered dead.
		return getPosition() >= 0.0f && getPosition() < getScreenLength(); // if it appears within the sight, it will be considered alive. otherwise, dead.
	}
};

// Cannonball is similar to Bullet, but it has no clue where it moves, because it has no direction info from its shape.
// So it contains direction information. A Cannonball user should decide which direction it moves.
class Cannonball : public Bullet {
	Direction direction;
public:
	Cannonball(Renderer& renderer, int player_pos = -1, Direction direction = Direction::Left, const char* shape = "*" )
		: Bullet(renderer, player_pos, shape), direction(direction) {}

	Direction getDirection() const { return direction; }

	void update()
	{
		if (isAlive() == false) return;
		// using direction info, it moves forward accordingly.
		if (direction == Direction::Left) move(-1.0f);
		else move(1.0f);
	}
};

// a PenetrableCannonball user should specify the shape info during initialization.
// otherwise, its appears inappropriately.
class PenetrableCannonball : public Cannonball {	
public:
	PenetrableCannonball(Renderer& renderer, int player_pos = -1, Direction direction = Direction::Left) 
		: Cannonball(renderer, player_pos, direction, direction == Direction::Left ? "<-" : "->") {}

	void hit() { setDamagePower(getDamagePower()- 0.2f); };
};

#endif
