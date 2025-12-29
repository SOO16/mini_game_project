#include "util.h"

int main(){

    // TITLE
    // - todo : 프로그램 종료되거나, 중간에 다른 이름으로 바뀐다
    SetConsoleTitleA("미로 탈출 게임");

    // LOAD MAP
    char map[SIZE][SIZE + 1];

    FILE* f = fopen("map.txt", "r");
    loadfMap(f, map);
    
    // INIT STATUS
    Status game_status = STAT_RUNNING;
    int size = SIZE;

    Player now;
    now.y = 1, now.x = 1, now.hp = 100;

    gotoYX(size, 0);
    printf("HP : 100");
    gotoYX(now.y, now.x);
    printf("@");

    Player tmp;
    tmp.y = now.y,tmp.x = now.x;

    // RUN GAME
    while (1) {
        
        // 방향키로 Player이동
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            (tmp.x)--;
            move(&now.y, &now.x, &now.hp, &tmp.y, &tmp.x, map, &game_status);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            (tmp.x)++;
            move(&now.y, &now.x, &now.hp, &tmp.y, &tmp.x, map, &game_status);
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            (tmp.y)--;
            move(&now.y, &now.x, &now.hp, &tmp.y, &tmp.x, map, &game_status);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            (tmp.y)++;
            move(&now.y, &now.x, &now.hp, &tmp.y, &tmp.x, map, &game_status);
        }

        // 프로그램 종료 (HP: 0)
        if (now.hp == 0) {
            game_status = STAT_LOSE;
            toggleWindowColorResult(&game_status);
            break;
        }

        // 프로그램 종료 (WIN or LOSE)
        if (game_status != STAT_RUNNING) {
            gotoYX(SIZE + 1, 0);
            break;
        }

        // 프로그램 종료 키 (ESC)
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            gotoYX(SIZE + 1, 0);
            break;
        }

        Sleep(100);
    }
    fclose(f);

	return 0;
}
