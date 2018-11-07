#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <cstring>

class GameObject {
	Renderer& renderer;
	float pos;
	char shape[100];

public:
	GameObject(Renderer& renderer, int pos, const char* shape) : renderer(renderer), pos(pos) { strcpy(this->shape, shape); }
	virtual ~GameObject() {} // very important!!!

	void setPosition(float pos) { this->pos = pos; }
	float getPosition() const { return pos; }

	void setShape(const char* shape) { if (!shape) return;  strcpy(this->shape, shape); }
	const char* getShape() const { return shape; }
	int getShapeSize() const { return strlen(shape); }

	void move(float inc) { pos += inc; }
	virtual void update() {}
	virtual void draw() { drawToRenderer(shape, pos); }

	void drawToRenderer(const char* shape, int pos) { renderer.draw(shape, pos); }

	int getScreenLength() const { return renderer.getScreenLength(); }
};

class Damageable {
	float damageRatio;

public:
	Damageable(float damageRatio) : damageRatio(damageRatio) {}

	float getDamage() { return damageRatio; }

	void setDamageRatio(float damageRatio) { this->damageRatio = damageRatio; }

	virtual bool getDamagedIfAttacked(const GameObject& attacker) = 0;	
};

enum class Direction {
	Left = 0,
	Right
};

#endif