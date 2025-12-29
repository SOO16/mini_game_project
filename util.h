#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

// Map size
#define SIZE    20
#define TEST_SIZE   5

// Player 구조체
typedef struct {
    int y, x, hp;
}Player;

// 게임 상태 열거형
typedef enum { STAT_RUNNING, STAT_WIN, STAT_LOSE } Status;

// txt 파일에서 맵 읽어오는 함수
void loadfMap(FILE* f, char map[][SIZE + 1]);

// map 출력 함수
void loadMap(char map[][SIZE + 1]);

// 커서 위치 제어 함수
void gotoYX(int y, int x);

// 위치 갱신 함수(이전 위치 @ 삭제)
void deleteBeforePos(int y, int x, char map[][SIZE + 1]);

// 윈도우 색상 토글 함수 (승리/패배 시)
void toggleWindowColorResult(Status* r);

// 위치 갱신 함수
void updatePos(int* ny, int* nx, int* ty, int* tx, char map[][SIZE + 1]);

// HP 상태 갱신 함수
void updateHp(int* hp);

// Player 이동 함수
void move(int* ny, int* nx, int* hp, int* ty, int* tx, char map[][SIZE + 1], Status* stat);
