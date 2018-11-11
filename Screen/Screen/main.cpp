#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <conio.h>
#include "Players.h"
#include "Enemies.h"
#include "Bullets.h"

int main()
{
	Players players;
	Enemies enemies(players);
	Bullets bullets(players, enemies);
	
	clock_t current_tick, start_tick;

	start_tick = clock();
	auto main = players.getMainCharacter();
	while (true)
	{
		current_tick = clock();
		Renderer::getInstance().clear();

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'a': case 75:
				players.move(-1);
				break;
			case 'd': case 77:
				players.move(1);
				break;
			case 72:
				break;
			case 80:
				break;
			case ' ':
				bullets.fire();
				break;
			}				
		}
		enemies.update();
		bullets.update();
		players.update();
		main = players.getMainCharacter();
		if (main == nullptr) break;
		
		enemies.draw();
		bullets.draw();
		players.draw();
		
		Renderer::getInstance().render();
		Sleep(66 - (clock()- current_tick));
	}
	system("cls");
	Borland::gotoxy(0, 1); 
	cout << enemies.getNumberOfKilled() << " enemies were killed, survival duration : "
		<< ((clock() - start_tick) / CLOCKS_PER_SEC) << " seconds\n";

	return 0;
}