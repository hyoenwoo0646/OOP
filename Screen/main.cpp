#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

int main()
{
	const int screen_size = 80;
	char screen[screen_size + 1];
	char player_face[] = "(^__^)";
	int player_pos = 20;
	char enemy_face[] = "(*--*)";
	int  enemy_pos = 60;
	const int max_bullets = 100;
	char bullet_face[] = "+";
	int bullet_positions[max_bullets];

	for (int i = 0; i < max_bullets; ++i)
		bullet_positions[i] = -1;

	while (true)
	{
		for (int i = 0; i < screen_size; i++) screen[i] = ' ';
		screen[screen_size] = '\0';

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player_pos = (player_pos - 1) % screen_size;
				break;
			case 'd':
				player_pos = (player_pos + 1) % screen_size;
				break;
			case ' ':
				int i = 0;
				for (; i < max_bullets; i++) {
					if (bullet_positions[i] == -1) break;
				}
				if (i < max_bullets) {
					bullet_positions[i] = player_pos;
				}
				break;
			}
		}
		draw(&screen[player_pos], player_face);
		draw(&screen[enemy_pos], enemy_face);
		for (int i = 0; i < max_bullets; ++i)
		{
			if (bullet_positions[i] == -1) continue;
			draw(&screen[bullet_positions[i]], bullet_face);
		}

		// update
		enemy_pos = (enemy_pos + rand() % 3 - 1) % screen_size;
		for (int i = 0; i < max_bullets; ++i)
		{
			if (bullet_positions[i] == -1) continue;
			if (bullet_positions[i] < enemy_pos) {
				bullet_positions[i] = (bullet_positions[i] + 1) % screen_size;
			}
			else if (bullet_positions[i] > enemy_pos) {
				bullet_positions[i] = (bullet_positions[i] - 1) % screen_size;
			}
			else {
				bullet_positions[i] = -1;
			}
		}

		Sleep(66);
	}


	return 0;
}