#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <cstring>

class GameObject {
	float pos;
	char shape[100];

public:
	GameObject(int pos, const char* shape) : pos(pos) { strcpy(this->shape, shape); }
	virtual ~GameObject() {} // very important!!!

	void setPosition(float pos) { this->pos = pos; }
	float getPosition() const { return pos; }

	void setShape(const char* shape) { if (!shape) return;  strcpy(this->shape, shape); }
	const char* getShape() const { return shape; }
	int getShapeSize() const { return strlen(shape); }

	void move(float inc) { pos += inc; }
	virtual void update() {}
	virtual void draw() {}
};

#endif