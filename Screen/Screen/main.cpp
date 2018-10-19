#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <conio.h>

using namespace std;

/*
1. Enemy hp 부여, 초기값 hp = 10, hp == 0이 되면 적은 죽으며 화면에서 보이지 않음.
2. 죽은 적에게 공격 불가
3. 연사 기능 제공, 플레이어는 최대 10발을 1프레임 간격으로 쏠 수 있음.스페이스바로 총을 쏠 수 있음.탄창이 비었다면 2초간 cool time 적용하여 총을 쏠 수 없음.
4. 총알은 적에게 1의 데미지를 줌
5. 적은 게임 시작후, 임의의 위치에서 spawn 가능함.
6. 한번에 spawn된 적은 최대 5개임.
7. 적은 플레이어에게 1초에 2칸씩(0.5초에 1칸) 이동함.
8. 적과 플레이어 간격이 2칸 이내일 때는 플레이어는 1초당 2만큼 데미지를 받음(매 프레임마다 지속적으로 데미지가 깍임)
9. 플레이어가 데미지를 받는 동안 플레이어 모습을 깜박깜박 거림.데미지를 받지 않으면 원상 복귀.
10. 플레이어가 죽으면 게임이 종료되고 죽은 적의 수와 플레이어가 살아있던 시간을 화면에 보여줌

NOTE:
현재 코드는 플레이어와 적간의 거리차 구하는 로직이 매우 단순하게 표현되어 있음. 수정이 필요함.
총알 이동시 적과 총알간의 거리에 대한 충분한 고려가 되어 있지 않음.

*/

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