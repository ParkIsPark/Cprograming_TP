#include "Maingame_header.h"



#define FLAGS_FALSE 2 // 페널티 깃발 갯수
#define FLAGS_TRUE 1 // 일반 깃발 갯수
#define MAX_X 50 //맵의 x축 방향 크기
#define MAX_Y 15 //맵의 y축 방향 크기

int locate_flags_false[FLAGS_FALSE][2]; // 페널티 깃발이 생성된 (x, y) 좌표를 저장하는 배열
int locate_flags_true[FLAGS_TRUE][2]; // 일반 깃발이 생성된 (x, y) 좌표를 저장하는 배열

int locate_player[1][2] = {
	{0,}
}; // 플레이어가 위치한 (x, y) 좌표를 저장하는 배열

void base_setting(void); // 콘솔창 및 난수 등의 기본 요소 설정
void textcolor(int color_number); //콘솔창 텍스트 색깔 설정
void gotoxy(int x, int y); // 콘솔창 커서 이동
void on_flag_false(void); // 플레이어가 깃발에 위치할 때
int check_flag_true(void); // 플레이어가 모은 일반 갯발을 확인
/*

1. 쉬움 맵 디자인(O)
	-> 맵 크기 쉬움 난이도 기준 50 * 15(O), 맵 크기는 변동 가능(커지든 작아지든)
	-> 장애물 생성(O)

2. 깃발 위치 랜덤 출력(O)
	-> 단 처음 플레이어의 스폰 위치(1, 13)에서는 깃발이 생성되지 X(O)

3. 깃발 갯수(O)
	-> 기호 상수 정의, 일단은 쉬움 기준 3개(O)
	-> 페널티 깃발, 일반 깃발 구분, 쉬움 기준 -> 페널티 : 일반 = 1: 2(O)
	-> 일반 깃발을 모두 모아야 해당 맵 클리어(O)

4. 깃발에 닿을 시 이벤트 출력(△)
	-> 각 깃발의 x, y좌표를 저장 후 플레이어의 좌표와 일치할 경우 이벤트 발생(O)
	-> 일반 깃발 다 모을 경우 성공 화면 출력 및 프로그램 종료(O)

	-> 무슨 이벤트가 일어날지 생각(△)
	-> 보상 깃발 요소는 난이도 중부터 고려 ex) 벌칙 깃발과 일반 깃발의 색 구분
	-> 벌칙 요소 필요

5. 움직이는 액션(△)
	-> 맵의 경계를 뚫지 못하게 처리(O)
	-> 장애물을 뚫지 못하게 처리(X)


---------------------------------- 코드는 이후 진도 학습이나 인터넷 참고로 더 간단하게 표현이 가능하면 수정 가능 -------------------------------------------


아이디어: 벌칙만 주는 깃발, 진짜 깃발, 퀴즈를 맞추면 보상, 틀리면 벌칙만 주는 깃발
	
	-> 퀴즈 요소 예시:
		1. C프로그래밍 일반 지식
		2. 컴퓨터공학개론 일반 지식
		3. 
		4.
		5.

	-> 벌칙 요소 예시: 
		1. 시간 감소
		2. 체력 감소
		3. 감시자 엔티티 추가 - ex) 감사 소프트웨어 or 백신
		4. 남은 깃발 위치 변경
		5. 난이도 어려움의 경우 벌칙 X, 바로 Game Over(당연히 벌칙만 주는 깃발도 X)

	-> 보상 요소 예시:
		1. 페널티 깃발과 일반 깃발의 색 구분
		2. 페널티 깃발 제거
		3. 점수 증가
		4. 시간 증가
		5. 체력 증가
		6. 장애물 제거
*/

int main(void)
{
	base_setting();
	
	int x = 1, y = (MAX_Y - 2), ch;

	while (1)
	{
		gotoxy(x, y);
		printf("*\b");

		locate_player[0][0] = x;
		locate_player[0][1] = y;

		on_flag_false(); // 플레이어가 페널티 깃발을 얻었는지 확인

		if (check_flag_true()) // 플레이어가 일반 깃발을 얻었는지, 다 모았는지 확인
		{
			Sleep(1000); // 다 모은 경우 성공 화면 출력, 1초 후 프로그램 종료
			break;
		}

		ch = _getch();

		if (ch == 224) // 방향키 처리
		{
			ch = _getch();

			switch (ch) {
			
			case 72:
				if (y == 1)
					break;
				y--;
				break;
			case 80:
				if (y == (MAX_Y - 2))
					break;
				y++;
				break;
			case 75:
				if (x == 1)
					break;
				x--;
				break;
			case 77:
				if (x == (MAX_X - 2))
					break;
				x++;
				break;
			}
		}

	}
}

void base_setting(void) // 콘솔창 및 난수 등의 기본 요소 설정
{
	srand((unsigned)time(NULL));

	system("mode con: cols=200 lines=15"); // 콘솔창의 크기 설정, cols = 행, lines = 열
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = FALSE; // 마우스 커서가 보이지 않게 설정, 다만, 원인불명으로 커서가 보임
	ConsoleCursor.dwSize = 1; // 커서의 사이즈
	textcolor(11); // 출력될 텍스트의 색상

	for (int i = 0; i < MAX_Y; i++) // 기본 맵 출력, 출력 방식 수정이 필요할 수도 있음
	{
		if (i == 0)
			printf("┌────────────────────────────────────────────────┐");

		
		else if (i == (MAX_Y - 1))
			printf("└────────────────────────────────────────────────┘");

		else
			printf("│                                                │");

		printf("\n");
	}

	for (int i = 2; i < MAX_Y - 2; i++) // 장애물이 생성될 위치 결정(맨 첫 줄과 맨 아랫 줄 제외)
	{
		for (int j = 1; j < rand() % 30; j++) // x축에서 생성할 장애물 갯수 랜덤 지정
		{
			gotoxy(2 + rand() % (MAX_X - 4), i); // 장애물 배치
			printf("▩");
		}
	}

	for (int i = 0; i < (FLAGS_TRUE + FLAGS_FALSE); i++) // 깃발이 생성될 위치 결정 및 좌표 저장
	{
		int x_locate = 1 + rand() % (MAX_X - 3); // 깃발이 오른쪽 벽을 뚫는 오류 발생
		int y_locate = 1 + rand() % (MAX_Y - 2);

		if (x_locate == 1 && y_locate == (MAX_Y - 2)) // 스폰 위치에 생성되지 않음
		{
			i--;
			continue;
		}

		if (i < FLAGS_TRUE) // 진짜 깃발의 위치 저장
		{
			gotoxy(x_locate, y_locate);
			printf("▶"); // 깃발 디자인 후보군 ▩★■▤▥▷▶

			locate_flags_true[i][0] = x_locate;
			locate_flags_true[i][1] = y_locate;
		}

		else // 가짜 깃발의 위치 저장
		{
			gotoxy(x_locate, y_locate);
			printf("▶"); // 깃발 디자인 후보군 ▩★■▤▥▷▶

			locate_flags_false[i - FLAGS_TRUE][0] = x_locate;
			locate_flags_false[i - FLAGS_TRUE][1] = y_locate;
		}

	}
}

void textcolor(int color_number) // 콘솔창 텍스트 색깔 설정
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number); // color_number이 11이라서 11의 색상 출력
}

void gotoxy(int x, int y) // 콘솔창 커서 이동
{
	COORD Cur = { x, y };
	printf(" ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void on_flag_false(void) // 플레이어가 페널티 깃발에 위치할 때
{
	for (int i = 0; i < FLAGS_FALSE; i++) // 플레이어가 페널티 깃발에 위치하는지 확인, 위치하면 이벤트 발생
	{
		if (locate_flags_false[i][0] == locate_player[0][0] && locate_flags_false[i][1] == locate_player[0][1])
		{
			gotoxy(70, 2);
			printf("페널티 깃발입니다!");
			Sleep(3000);

			gotoxy(70, 4);
			printf("문제를 푸셔야 나갈 수 있습니다.");
			
			gotoxy(70, 5);
			printf("방향키를 누르면 다시 맵으로 돌아갑니다."); // 현재는 만들어둔 문제가 없어서 바로 넘어옴
		}
	}
}

int check_flag_true(void) // 플레이어가 일반 깃발에 위치할 때
{
	static int count = 0;
	
	for (int i = 0; i < FLAGS_TRUE; i++) // 플레이어가 일반 깃발에 위치하는지 확인, 위치하면 이벤트 발생
	{
		if (locate_flags_true[i][0] == locate_player[0][0] && locate_flags_true[i][1] == locate_player[0][1])
			count++;
	}

	if (count == FLAGS_TRUE) // 모든 일반 깃발을 다 모은 경우
	{
		system("cls");

		gotoxy(17, 7);
		printf("모든 일반 깃발을 다 모았습니다!");

		return 1;
	}

	return 0;
}