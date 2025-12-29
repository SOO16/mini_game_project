#include "util.h"

// txt 파일에서 맵 읽어오는 함수
void loadfMap(FILE* f, char map[][SIZE + 1]) {
    if (!f) { printf("MAP LOAD ERROR!\n"); }

    for (int i = 0; i < SIZE; ++i) {
        if (fscanf(f, " %20[^\n]", map[i]) != 1) {
            for (int j = 0; j < SIZE; ++j) map[i][j] = ' ';
            map[i][SIZE] = '\0';
            continue;
        }
        int len = (int)strlen(map[i]);
        for (int j = len; j < SIZE; ++j) map[i][j] = ' ';
        map[i][SIZE] = '\0';
    }

    // map 출력
    for (int i = 0; i < SIZE; ++i) puts(map[i]);
}

// map 출력 함수
void loadMap(char map[][SIZE + 1]) {
    for (int i = 0; i < SIZE; ++i) puts(map[i]);
}

// 커서 위치 제어 함수
void gotoYX(int y, int x) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;  // COORD : Console의 position 구조체 (Y, X)
    pos.Y = y;
    pos.X = x;

    SetConsoleCursorPosition(hConsole, pos);
}

// 위치 갱신 함수(이전 위치 @ 삭제)
void deleteBeforePos(int y, int x, char map[][SIZE + 1]) {
    gotoYX(y, x);
    printf("%c", map[y][x]);
}

// 윈도우 색상 토글 함수 (승리/패배 시)
void toggleWindowColorResult(Status* r) {
    if (*r == STAT_WIN) {
        for (int i = 0; i < 3; i++) {
            system("color AF");
            Sleep(100);
            system("color 07");
            Sleep(100);
        }
    }
    if (*r == STAT_LOSE) {
        for (int i = 0; i < 3; i++) {
            system("color 4F");
            Sleep(100);
            system("color 07");
            Sleep(100);
        }
    }
    else return;
}

// 위치 갱신 함수
void updatePos(int* ny, int* nx, int* ty, int* tx, char map[][SIZE + 1]) {
    deleteBeforePos(*ny, *nx, map);
    *ny = *ty;
    *nx = *tx;
    gotoYX(*ny, *nx);
    printf("@");
}

// HP 상태 갱신 함수
void updateHp(int* hp) {
    gotoYX(SIZE, 0);
    printf("HP : %d  ", *hp);
}

// Player 이동 함수
void move(int* ny, int* nx, int* hp, int* ty, int* tx, char map[][SIZE + 1], Status* stat) {
    if (map[*ty][*tx] == '#') {
        *ty = *ny;
        *tx = *nx;
        return;
    }
    if (map[*ty][*tx] == ' ') {
        updatePos(ny, nx, ty, tx, map);
        return;
    }
    if (map[*ty][*tx] == '^') {
        updatePos(ny, nx, ty, tx, map);
        *hp -= 10;
        updateHp(hp);
        return;
    }
    if (map[*ty][*tx] == 'a') {
        updatePos(ny, nx, ty, tx, map);
        *hp = 100;
        updateHp(hp);
        return;
    }
    if (map[*ty][*tx] == 'M') {
        updatePos(ny, nx, ty, tx, map);
        *hp = 0;
        updateHp(hp);
        *stat = STAT_LOSE;
        toggleWindowColorResult(stat);
        return;
    }
    if (map[*ty][*tx] == 'Y') {
        updatePos(ny, nx, ty, tx, map);
        *stat = STAT_WIN;
        toggleWindowColorResult(stat);
        return;
    }
    else return;
    Sleep(20);
}
