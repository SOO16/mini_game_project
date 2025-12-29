#include "game_example.h"

// 20*20 크기 맵
char map[n][n + 1] = {
	"####################",
	"# # ^ #Y  ###Ma ^^ #",
	"# ^ M  ##M#######^##",
	"#####M  #^     M#  #",
	"#  ^   #MM M#M  ^^ #",
	"#  ##^ #^  ^#####  #",
	"#M  ^^#M #MY^ ^## M#",
	"# ^# M#^ ###^   #^M#",
	"# ^# ^M M### # M#  #",
	"#  #Ma#  MYM # ^#M^#",
	"# ^  Ma# ###^#M^#  #",
	"#^###### ###^#^^^  #",
	"#^## M ^  ^ ^ ###  #",
	"#^## ^^##M#a# ##  ##",
	"#^## ^#^^Y#######^^#",
	"#^   ## ###M #   ^^#",
	"# ###aM^ ^^^^  # ###",
	"# ########### ^#  ##",
	"#             ^#M aM",
	"####################",
};

int used[n][n] = { 0 };	//아이템 획득 여부 체크하는 배열 (1: 획득함, 0: 획득 전)

int y = 1, x = 1;		// 캐릭터(@)의 현재 위치
int hp = MAX_HP;		// 캐릭터의 체력
int state = 0;			// 함정 중복 데미지를 방지하기 위한 플래그 (0: 대기, 1: 피격상태)
int isRunning = 1;		// 게임 실행 상태 플래그 (1: 실행중, 0: 종료)


// 함수 선언
// 맵, 캐릭터 상태 등 화면 출력 함수
void printMap() {
	// 1. 현재 커서를 0,0 위치로 이동
	COORD pos = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	// 2. 맵 출력
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (y == i && x == j) printf("@");
			else if (used[i][j])	printf(" ");
			else printf("%c", map[i][j]);
		}
		printf("\n");
	}
	// %-3d : 3자리를 무조건 채워야 한다
	printf("HP : %-3d\n", hp);
}

// 사용자 입력 처리 함수
void handleInput() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (isValid(y, x - 1)) {
			x--;
			state = 0;	// 이동 성공 시 state를 0으로 초기화 (함정)
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (isValid(y, x + 1)) {
			x++;
			state = 0;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (isValid(y - 1, x)) {
			y--;
			state = 0;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (isValid(y + 1, x)) {
			y++;
			state = 0;
		}
	}
}

// 벽 체크 (0: 벽, 1: 갈 수 있는 곳)
int isValid(int y, int x) {
	return (map[y][x] != '#');
}

// 이동 로직 처리 함수
void handleLogic() {
	// 가시 함정
	if (map[y][x] == '^') {
		hpDown();
		if (hp <= 0)
			gameOver();
	}

	// 회복 아이템	
	else if (map[y][x] == 'a' && used[y][x] == 0) {
		hpUp();
	}

	// 게임 종료 (패배, M)
	else if (map[y][x] == 'M') {
		gameOver();
	}

	// 게임 종료 (승리, Y)
	else if (map[y][x] == 'Y') {
		gameWin();
	}
}

// 회복 아이템
void hpUp() {
	hp = MAX_HP;
	// Todo: 회복 아이템을 먹으면 사라져야 한다
	used[y][x] = 1;
}

// 가시 함정
void hpDown() {
	if(state == 0) {
		hp -= 10;
		state = 1;
	}

}

// 게임 종료 (패배, M)
void gameOver() {
	system("color 0F");
	Sleep(100);
	system("color 4F");
	Sleep(200);
	
	system("color 0F");
	Sleep(100);
	system("color 4F");
	Sleep(200);

	system("cls");
	printf("GAME OVER!!!!!!!!!!!!!");

	isRunning = 0;	// 전체 반복 종료
}

// 게임 종료 (승리, Y)
void gameWin() {
	system("color 0F");
	Sleep(100);
	system("color 2F");
	Sleep(200);

	system("color 0F");
	Sleep(100);
	system("color 2F");
	Sleep(200);

	system("cls");
	printf("GAME WIN!!!!!!!!!!!!!");

	isRunning = 0;	// 전체 반복 종료
}