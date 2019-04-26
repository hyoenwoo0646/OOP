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

const int screen_size = 80;

class Player {
	int pos;
	int hp;
	int mp;
	char face[20];

public:
	Player(int position, int hp, int mp, const char* face)
		: pos(position), hp(hp), mp(mp)
	{
		strcpy(this->face, face);
	}

	void increasePosition(unsigned int inc)
	{
		if (this->pos + inc >= screen_size) return;
		this->pos = this->pos + inc;
	}

	void setPosition(int pos) // setter
	{
		this->pos = pos;
	}

	int getPosition() // getter on "pos"
	{
		return pos;
	}

};

class Enemy {

};

class Bullet {

};

int main()
{
	char screen[screen_size + 1];
	Player player(30, 10, 10, "(^_^)");
	Enemy enemy;
	Bullet bullet;

	player.setPosition(20);

	while (true)
	{
		for (int i = 0; i < screen_size; i++) screen[i] = ' ';
		screen[screen_size] = '\0';

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.pos = (player.pos - 1) % screen_size;
				break;
			case 'd':
				player.pos = (player.pos + 1) % screen_size;
				break;
			case ' ':
				bullet.pos = player.pos;
				break;
			}
		}
		player.draw(screen);
		enemy.draw(screen);
		if (bullet.pos != -1)
			bullet.draw(screen);

		// update
		enemy.pos = (enemy.pos + rand() % 3 - 1) % screen_size;
		if (bullet.pos != -1) {
			if (bullet.pos < enemy.pos) {
				bullet.pos = (bullet.pos + 1) % screen_size;
			}
			else if (bullet.pos > enemy.pos) {
				bullet.pos = (bullet.pos - 1) % screen_size;
			}
			else {
				bullet.pos = -1;
			}
		}
		
		printf("%s\r", screen);
		Sleep(66);
	}


	return 0;
}