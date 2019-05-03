// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) {}
	~Screen() { delete[] screen; }

	void draw(int pos, const char* face) 
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render() 
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class Player {
	int pos;
	char face[20];
	Screen* screen;

public:
	Player(int pos, const char* face, Screen* screen) : pos(pos), screen(screen)
	{
		strcpy(this->face, face);
	}

	void setPosition(int pos) // setter
	{
		this->pos = pos;
	}

	int getPosition() // getter on "pos"
	{
		return pos;
	}

	void moveLeft()
	{
		pos--;
	}

	void moveRight()
	{
		pos--;
	}

	void draw()
	{
		screen->draw(pos, face);
	}

	void update()
	{

	}

};

class Enemy {
	int pos;
	char face[20];
	Screen* screen;

public:
	Enemy(int pos, const char* face, Screen* screen) : pos(pos), screen(screen)
	{
		strcpy(this->face, face);
	}

	void setPosition(int pos)
	{
		this->pos = pos;
	}

	int getPosition()
	{
		return pos;
	}

	void draw()
	{
		screen->draw(pos, face);
	}

	void moveRandom()
	{
		pos = pos + rand() % 3 - 1;
	}

	void update()
	{
		moveRandom();
	}
};

class Bullet {
	int pos;
	char face[20];
	bool isFiring;
	Screen* screen;

public:
	Bullet(int pos, const char* face, Screen* screen) : pos(pos), isFiring(false), screen(screen)
	{
		strcpy(this->face, face);
	}

	void setPosition(int pos)
	{
		this->pos = pos;
	}

	int getPosition()
	{
		return pos;
	}

	void moveLeft()
	{
		pos--;
	}

	void moveRight()
	{
		pos--;
	}

	void draw()
	{
		if (isFiring == false) return;
		screen->draw(pos, face);
	}

	void fire(int player_pos)
	{
		isFiring = true;
		pos = player_pos;
	}

	void update(int enemy_pos)
	{
		if (isFiring == false) return;
		if (pos < enemy_pos) {
			pos = pos + 1;
		}
		else if (pos > enemy_pos) {
			pos = pos - 1;
		}
		else {
			isFiring = false;
		}
	}
};

int main()
{
	Screen screen{ 80 };
	Player player = { 30, "(^_^)", &screen };
	Enemy enemy{ 60, "(*--*)", &screen };
	Bullet bullet( -1, "+", &screen);

	while (true)
	{
		screen.clear();

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				bullet.fire(player.getPosition());
				break;
			}
		}
		player.draw();
		enemy.draw();
		bullet.draw();

		player.update();
		enemy.update();
		bullet.update(enemy.getPosition());
		
		screen.render();
		Sleep(66);
	}

	return 0;
}