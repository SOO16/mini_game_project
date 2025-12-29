#include "game_example.h"

int main() {
	while (isRunning) {
	    printMap();			// 맵, 캐릭터 상태 등 화면 출력 함수
		handleInput();		// 사용자 입력 처리 함수
		handleLogic();		// 이동 로직 처리 함수
		Sleep(100);			// 너무 빠른 입력 처리를 막기 위한 딜레이
	}
	return 0;
}