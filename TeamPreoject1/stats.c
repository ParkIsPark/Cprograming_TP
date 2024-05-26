// Last Edit: 2024-05-15 00:17
#include "default_header.h"

extern int game_score; // 'game_score' variable declared in main file
extern int battery; // 'battery' variable declared in main file
extern int difficulty; // 1: Easy to Normal, 2: Normal to Hard, 3: Game End / declared in main file / init to 0 (Game Start)

// Adjusting Score (Args: score to add or subtract)
void add_score(int plus) {
	// goto(x,y); // locate where to print startpoint (cursor position) or if you want, use goto before call this function for legibility
	printf("점수를 %d점 얻고 ", game_score);
	game_score += plus;
	printf("%d점이 되었다.", game_score);
}
void sub_score(int minus) {
	// goto(x,y);
	printf("점수를 %d점을 잃고 ", game_score);
	game_score -= minus;
	printf("%d점이 되었다.", game_score);
}


// Adjusting Battery (Args: amount of charged or used)
void char_battery(int amount) {
	// goto(x,y);
	printf("배터리를 %d%% 소모하고 ", battery);
	battery -= amount;
	printf("%d%%가 남았다.", battery);
}
void use_battery(int amount) {
	// goto(x,y);
	printf("배터리를 %d%% 소모하고 ", battery);
	battery -= amount;
	printf("%d%%가 남았다.", battery);
}


// Bug Found (Args: what kind of bug is)
void find_bug(int bugs) {
	// goto(x,y)
	switch (bugs) {
	case 1:
		printf("Game1 실행");
		game1();
		break;
	case 2:
		printf("Game2 실행");
		game2();
		break;
	case 3:
		printf("Game3 실행");
		game3();
		break;
	case 4:
		printf("Game4 실행");
		game4();
		break;
		// add some cases more
	}
}


// Map Change
void map_change(void) {
	// goto(x,y);
	switch (difficulty) {
	case 0:
		printf("게임 시작 (난이도 쉬움)");
		break;
	case 1:
		printf("난이도 쉬움 -> 보통");
		break;
	case 2:
		printf("난이도 보통 -> 어려움");
		break;
	case 3:
		printf("게임 끝");
		break;
	}
}