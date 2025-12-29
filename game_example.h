#ifndef GAME_H
#define GAME_H

#include<stdio.h>
#include<Windows.h>

#define n 20				// 맵 크기
#define MAX_HP 100			// 최대 체력

//전역 변수
extern char map[n][n + 1];	// 20*20 크기 맵
extern int used[n][n];	//아이템 획득 여부 체크하는 배열 (1: 획득함, 0: 획득 전)
extern int y, x;			// 캐릭터(@)의 현재 위치
extern int hp;				// 캐릭터의 체력
extern int state;			// 함정 중복 데미지를 방지하기 위한 플래그 (0: 대기, 1: 피격상태)
extern int isRunning;		// 게임 실행 상태 플래그 (1: 실행중, 0: 종료)

//함수 선언
void printMap();			// 맵, 캐릭터 상태 등 화면 출력 함수
void handleInput();			// 사용자 입력 처리 함수
void handleLogic();			// 이동 로직 처리 함수
int isValid(int y, int x);	// 벽 체크 (0: 벽, 1: 갈 수 있는 곳)
void gameOver();			// 게임 종료 (패배, M)
void gameWin();				// 게임 종료 (승리, Y)
void hpUp();				// 가시 함정
void hpDown();				// 회복 아이템


#endif