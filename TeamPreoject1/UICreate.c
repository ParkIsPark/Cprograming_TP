#include "GameUI.h"



//스타트 게임 메뉴를 위한 define과 열거형들
#define Start_Menu_x 53//이거 바꾸면 startmenu가 그려지는 위치가 달라집니다
#define Start_Menu_y 18

#define diff_select_menu_x 53 //얘내를 바꾸면 난이도 선택 메뉴가 그려지는 위치가 달라집니다. 
#define diff_select_menu_y 18

typedef enum CursorInput {
	Start,///각각 0, 1, 2에 대응합니다
	Story,
	Quit
}CursorInput;

typedef enum difficultyy {
	Easy,///각각 0, 1, 2에 대응합니다
	Normal,
	Hard
}Gamedifficulty;
//

void Game_Start_Screen_draw()//게임 처음 시작할때 그림 그리는 함수
{
	gotoxy(45, 2);
	printf("_____    _____");
	Sleep(200);
	gotoxy(47, 3);
	printf("ll       ll");
	Sleep(200);
	gotoxy(47, 4);
	printf("-       -");
	Sleep(200);
	gotoxy(49, 7);
	printf("  ㅡ");
	Sleep(200);
	//동작 메커니즘 : 커서가 위로 가서 그림 그리고, 멈추고, 다시 그리고, 멈추고 반복
}

//메뉴 셀렉트할떄 사용되는 함수들
extern int Cursor_input;//밖에서 받아오는 매개변수임
void Game_Start_menu_Screen_draw(int Cursor_input)//스타트 메뉴 그려줌.
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 떄마다 바꿔줄 수 있음.
	{
		case Start://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
			printf(" ");
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//텍스트 파란색 배경 검은색. 커서를 바꿔줌.
			gotoxy(Start_Menu_x+1, Start_Menu_y); printf("게임시작");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y+2); printf("스토리");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
		case Story:
			printf(" ");//커서 지워주고
			gotoxy(Start_Menu_x, Start_Menu_y+2);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y + 2);
			break;
		case Quit:
			printf(" ");//커서 지워주고
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextColor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			break;
		default://가장 처음 입력되었을 때
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//텍스트 파란색 배경 검은색
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("게임시작");
			SetTextcolor(15, 0);//텍스트 하얀색 배경 검은색
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("스토리");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("종료");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
	}
}
void Game_Difficulty_Select_Screen_draw(int Cursor_input)
{
	switch (Cursor_input)//커서가 어디에 가있는지 확인받아서 입력받기 때문에, 바뀔 떄마다 바꿔줄 수 있음.
	{
	case Easy://글자색깔을 바꿔줄 수 없기 때문에, 항상 지우고 다시 그려줌.
		printf(" ");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);////////////////////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	case Normal:
		printf(" ");//커서 지워주고
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(1, 0);//////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		break;
	case Hard:
		printf(" ");//커서 지워주고
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("쉬움");
		SetTextColor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("보통");
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("어려움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		break;
	default://가장 처음 입력되었을 때
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);///////////////////////////////////////////////////
		gotoxy(diff_select_menu_x+1, diff_select_menu_y); printf("쉬움");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 2); printf("보통");
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 4); printf("어려움");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	}
}
int Game_Select_menu_control(int max_menu_amount, void(*SelectFp)(int))//메뉴가 최대 몇개인지 확인+함수 포인터 사용
{
	char ch;
	int Cursor_y = 0;

	while (1)//난이도 선택하는 과정
	{
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// 커서를 위로 이동, 순환하도록 수정
				SelectFp(Cursor_y);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// 커서를 아래로 이동, 순환하도록 수정
				SelectFp(Cursor_y);
				break;
			default:
				break;
			}
		}
		else if (ch == 13)
		{
			break;
		}
	}
	return Cursor_y;//커서가 어디에 있었는지 리턴, 0, 1, 2의 형태로 리턴함.
}//게임 메뉴 셀렉트를 도와주는 외부 함수임
//


void Game_Story_Select_Screen_draw()//스토리 고르는 화면.
{
	char story[] = "파일을 훔치러 왔다... 야압!!!!!";//스토리도 뭐쓸지 고민중
	system("cls");//항상 화면 초기화
	for (int i = 0; i < 30; i++) {
		printf("%c", story[i]);
		Sleep(50);//한글자한글자 출력
	}
}