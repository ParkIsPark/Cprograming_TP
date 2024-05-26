#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"//게임에 필요한 필수 기능들 넣어놓은 UI들.

static int ch;//사용자로부터 입력받는
static int x = 53, y = 18;//입력좌표
void setcolor(int txt, int bg);//텍스트와 배경 색갈 바꾸는 함수 txt에 텍스트 색갈 bg는 배경색갈
void CursorClosing();//커서 숨기는 함수
void menu();//첫번째 게임시작 스토리 종료 선택하는 함수
void draw();//그림 출력하는 함수
void menu1();//첫번째 메뉴함수에서 선택한후 출력하는 함수
void difficulty();//난이도 출력한후 선택하는 함수
void menu2();//선택한 난이도 출력하는 함수

int main() {
	
	system("title 게임파일 찾기");

	CursorView();//커서 지우기
	draw();//그림 출력
	setcolor(1, 0);//텍스트 파란색 배경 검은색
	gotoxy(54, 18); printf("게임시작");

	setcolor(15, 0);//텍스트 하얀색 배경 검은색
	gotoxy(55, 20);printf("스토리");

	gotoxy(56, 22);printf("종료");
	menu();
	system("cls");//화면 지우기
	menu1();
	
	
}




void menu1() {
	if ( y == 18) {
		gotoxy(54, 18);
		setcolor(1, 0);
		printf("쉬움");
		
		setcolor(15,0);
		gotoxy(54, 20);
		printf("보통");

		gotoxy(54, 22);
		printf("어려움");
		difficulty();
		system("cls");
		menu2();
	}
	else if (y == 22) {
		gotoxy(50, 15);
		printf("게임을 종료합니다");
		for (int i = 0; i < 13; i++)
			printf("\n");
		
	}
	else
	{
		char story[] = "파일을 훔치러 왔다... 야압!!!!!";//스토리도 뭐쓸지 고민중
		for (int i = 0; i < 30; i++) {
			printf("%c", story[i]);
			Sleep(50);//한글자한글자 출력
		}
	}
}
void menu2() {
	if (y == 18) {
		printf("쉬운난이도~")

			;
	}
	else if ( y == 20) {
		printf("보통~");
	}
	else if (y == 22)
		printf("어려움~");
	
}
void difficulty() {
	do {
		gotoxy(x, y);
		setcolor(15, 0);
		printf(">\b");
		ch = _getch();

		if (ch == 224) {

			printf(" ");
			ch = _getch();
			switch (ch) {
			case 72:
				if (y == 18) {
					y = 22;

					setcolor(15, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(15, 0);
					gotoxy(54, 20); printf("보통");

					setcolor(1, 0);
					gotoxy(54, 22); printf("어려움");
				}

				else if (y == 22) {
					y -= 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(1, 0);
					gotoxy(54, 20); printf("보통");
					setcolor(15, 0);
					gotoxy(54, 22); printf("어려움");
				}
				else if (y == 20) {
					y -= 2;
					setcolor(1, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(15, 0);
					gotoxy(54, 20); printf("보통");
					setcolor(15, 0);
					gotoxy(54, 22); printf("어려움");
				}
				break;
			case 80:
				if (y == 22) {
					y = 18;
					setcolor(1, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(15, 0);
					gotoxy(54, 20); printf("보통");
					setcolor(15, 0);
					gotoxy(54, 22); printf("어려움");
				}
				else if (y == 20) {
					y += 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(15, 0);
					gotoxy(54, 20); printf("보통");
					setcolor(1, 0);
					gotoxy(54, 22); printf("어려움");
				}

				else if (y == 18) {
					y += 2;
					setcolor(15, 0);
					gotoxy(54, 18); printf("쉬움");

					setcolor(1, 0);
					gotoxy(54, 20); printf("보통");
					setcolor(15, 0);
					gotoxy(54, 22); printf("어려움");
				}
				break;
			}

		}

	} while (ch != 13);


}

