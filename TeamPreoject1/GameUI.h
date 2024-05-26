#define _CRT_SECURE_NO_WARNINGS
#include "default_header.h"
#include "GameUtility.h"

void Game_Start_Screen_draw();//메인화면 그리는 함수
void Game_Start_menu_Screen_draw(int);//스타트 메뉴 그리는 함수
int Game_Select_menu_control(int, void*);//게임 UI 선택할 수 있게 해주는 함수.
void Game_Difficulty_Select_Screen_draw();
void Game_Story_Select_Screen_draw();