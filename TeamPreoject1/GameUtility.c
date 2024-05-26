#include "GameUtility.h"

extern int x, y;//외부 변수임을 정의
void gotoxy(int x, int y)//이동 함수, Minigame에서 선언된 xy를 게임유틸리티.h에서 받아서 리턴한다. 
{
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}//커서 이동시키는 함수

void CursorClosing() {//커서를 안 보이게 하는 함수
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void CursorView() {//커서를 보이게 하는 함수
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = TRUE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

extern int txt, bg;//외부변수임을 정의
void SetTextcolor(int txt, int bg) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);//작동 메커니즘상 bg는 배경 색깔, txt는 텍스트 색깔을 의미함
	//한번 바꿔놓으면 다시 바꾸기 전까지는 그 색깔을 그대로 유지함. 이때 바뀌는건 '새로 입력되는 텍스트의 색깔' 임
	//색상 한번 파란색으로 바꿨으면, 꼭 다시 원상태로 돌려놓을 것!
}
