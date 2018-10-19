#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <conio.h>

using namespace std;

#include "Players.h"
#include "Enemies.h"
#include "Bullets.h"


int main()
{
	Renderer renderer;
	Players players(&renderer);
	Player* main = players.getMainCharacter();
	Enemies enemies(&renderer, main);
	Bullets bullets(&renderer, &players, &enemies);
	
	clock_t current_tick, start_tick;

	start_tick = clock();
	while (true)
	{
		current_tick = clock();
		renderer.clear();

		if (_kbhit()) {
			char key = _getch();
			//printf("%d\n", key);
			if (key == 27) break;
			if (key == -32) {
				key = _getch();
			}

			switch (key) {
			case 'a': case 75:
				main->move(-1);
				break;
			case 'd': case 77:
				main->move(1);
				break;
			case 72:
				break;
			case 80:
				break;
			case ' ':
				bullets.fire(main);
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
		
		renderer.render();
		Sleep(66 - (clock()- current_tick));
	}
	renderer.clear();
	Borland::gotoxy(0, 1); printf("# of killed enemies = %d, elapsed survival duration = %d seconds\n", 
		enemies.getNumberOfKilled(),
		(clock() - start_tick) / CLOCKS_PER_SEC );

	return 0;
}