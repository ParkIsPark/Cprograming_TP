#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility 저장되어 있음.
//매개변수 정의, 나중에 난이도 나눌때 사용할 예정
#define Easy 3
#define Normal 6
#define Hard 9
#define Max_X 70//GatData게임에서 x축으로 퍼지는 정도
//
//전역변수 선언 시점
// 
//GetData용 전역변수들
typedef struct ObjectCoord//오브젝트 좌표값 저장해둘 스트럭쳐
{
	int x;//x값
	int y;//y값
	int speed;//속도
}ObjectCoord;
int FindDupli[8];//좌표값 할당 과정에서 중복 없도록 체크해주는 배열
//

void PWMiniGameLevel1(int);//게임 레벨이 1단계일 때 미니게임. DIfficult는 난이도, 시도 횟수를 정의함. 
void GetDataLevel1(int);//떨어지는 데이터를 성공적으로 줍는 게임
void ControlObjMove(ObjectCoord*, int, ObjectCoord, int*);//오브젝트들의 현재 위치 컨트롤
void ControlGoldMove(ObjectCoord*, int, char*, ObjectCoord, char*);//보상오브젝트들의 위치 컨트롤
void PlayerMoveControl(ObjectCoord*);//플레이어 위치 컨트롤
void MemoryReturnMiniGameLevel1(int);//추정 가능한 단어 조합을 나누고, 이를 조합하도록 만드는 것. 배열이 뒤섞였다는 컨셉. 
void Quiz(int);//퀴즈를 여러개 만들어서 파일로 저장할 것이므로, 매개변수를 잘 설정해놓을 것. 
void ClickMiniGameLevel1(int);//단순히 빠르게 클릭하는 미니게임. 

int main()
{
	srand((unsigned)time(NULL)); 
	GetDataLevel1(3);
	printf("끝");
	Sleep(2000);
	return 0; 
}
void PWMiniGameLevel1(int Difficult)
{
	srand((unsigned)time(NULL));
	char word[10];
	char input[10];
	int TryLimit, i;//반복문 제어용 변수, TryLimit는 비밀번호 제한
	TryLimit = Difficult;
//비밀번호 설정
	for (i = 0; i < 9; i++)
	{
		word[i] = 'a' + rand() % 25;
	}
	word[i] = '\0';
//비밀번호 설정
//
	for (; TryLimit > 0; TryLimit--)//난이도에 따라 주어지는 횟수만큼 만복
	{
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|           비밀번호: %s                           |\n", word);
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		Sleep(2000);
		system("cls");
		//
		//비밀번호 입력 받는 시퀀스
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|    비밀번호를 입력하세요                                |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		printf(":");
		gets_s(input, 10);//나중에 연결 리스트로 바꾸기. 
		///
		///성공, 실패 여부 판가름
		if (!(strcmp(word, input)))
		{
			printf("정답입니다.");
			//hp증가 등등의 특전 들어갈 자리
			// //성공시 종료
		}
		else
		{
			if (TryLimit-1)//시도 횟수 남아있는지 확인
			{
				printf("틀렸습니다. 기회는 %d번입니다", TryLimit-1);//틀리면 다시 반복
				Sleep(2000);
				system("cls");
			}
			else
			{
				printf("기회를 모두 소진하셨습니다. 디버프를 받습니다");
				//디버프 코드
			}
		}
	}
}
void GetDataLevel1(int Difficult)//상자 모양은 [문자], 흩어진 배열을 줍는 게임. 
{
	int GameHp = 3;//미니게임 hp
	char LostData[8] = " [Gold]"; //떨어질 문자열
	char GetData[7] = {0,};//떨어진 문자열 저장되는 배열
	float GameOverCount = 15;//게임에 주어지는 시간
	int IsFullCollect = 0;//전부 모았는지 확인하는 변수. 
	ObjectCoord D[3];//오브젝트 좌표값 저장하는 스토리지
	ObjectCoord B[5];
	ObjectCoord P1 = { 0, 29, 3};
	int i, j; //반복문 제어용 변수
	for (i = 0; i < 5; i++)//장애물 위치를 중복 없게끔 만들어주는 함수
	{
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 5; j++)
		{
			if (FindDupli[i] == FindDupli[j])//만약 중복이 있다면 다르게 만들어버림
			{
				FindDupli[i] = rand() % Max_X;
				continue;
			}
		}
	}
	for (i = 5; i < 8; i++)//보상 위치를 중복 없게끔 만들어주는 함수
	{
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 8; j++)
		{
			if ( abs(FindDupli[i] - FindDupli[j]) < 3 )//만약 3칸 이내에 장애물이나 다른 보상이 있다면
			{
				FindDupli[i] = rand() % Max_X;//다시 설정함
				continue;
			}
		}
	}
//일일히 할당
	for (i = 0; i < 5; i++) {
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = 0; i < 3; i++)
	{
		D[i].x = FindDupli[5+i];
		D[i].y = 0;
		D[i].speed = rand() % 10 + 1;
	}
//끝
	while (1)
	{
		system("cls");
		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < 5; i++) {
			ControlObjMove(&B[i], i, P1, &GameHp);
		}
		for (i = 0; i < 3; i++)
		{
			if (D[i].speed != -1)
			{
				ControlGoldMove(&D[i], 2*i, LostData, P1, GetData);
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//게임 종료 코드
		{
			break;
		}
		if (_kbhit())
		{
			PlayerMoveControl(&P1);
		}
		for (i = 0; i < 30; i++)
		{
			gotoxy(Max_X + 10, i);
			printf("|");
		}
		gotoxy(Max_X + 13, 5);
		printf("떨어지는 데이터를 주우세요!");
		gotoxy(Max_X + 13, 8);
		printf("남은 체력 : %d", GameHp);
		gotoxy(Max_X + 13, 12);
		printf("지금까지 주운 배열 : ");
		for (i = 0; i < 7; i++)
		{
			printf("%c", GetData[i]);
			if (GetData[i] == LostData[i + 1])
			{
				IsFullCollect += 1;
			}
		}
		if (IsFullCollect >= 6)
		{
			break;
		}
		IsFullCollect = 0;
		gotoxy(Max_X + 13, 15);
		printf("남은 시간 : %.f", GameOverCount);
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			if (_kbhit())
			{
				PlayerMoveControl(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//플레이어 위치를 계속 체크해주면서 딜레이 해소
		{
			PlayerMoveControl(&P1);
		}
		GameOverCount -= 0.2f;
		
	}//게임 코드
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < 6; i++)
	{
		if (GetData[i] == LostData[i+1])//로스트
		{
			IsFullCollect += 1;
		}
	}
	printf("----------------------------------------------------------\n");//화면 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      완료율 = %.lf%%                        |\n", (IsFullCollect/6.0)*100);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
//GetData 미니게임에서 쓰이는 함수들
void ControlObjMove(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp)//오브젝트 움직임을 담당
{
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < 5)//hp감소 로직
		{
			(*Hp)--;
		}
		gotoxy(Obje1->x, Obje1->y-1);//삭제 로직
		printf(" ");
		FindDupli[i] = rand() % Max_X;
		for (j = 0; j < 5; j++)
		{
			if (FindDupli[i] == FindDupli[j])//만약 중복이 있다면 다르게 만들어버림
			{
				FindDupli[i] = rand() % Max_X;
				continue;
			}
		}
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("*");
	Obje1->y += Obje1->speed;
	return;
}//별 움직임 제어
void ControlGoldMove(ObjectCoord* Obje1, int i, char* GoldText, ObjectCoord Player, char* GetText)
{
	int t = 0;//밑에.. 대충 뭔가에서 사용하는ㄱ것
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < 7)//닿았는지 확인하는 로직
		{
			t = i;
			for (j = 1+i; j <= 2+i; j++)
			{
				GetText[t] = GoldText[j];
				t++;
			}
			Obje1->speed = -1;
			gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
			printf("     ");
			Obje1->y = 0;
			return;
		}
			gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
			printf("     ");
			FindDupli[i] = rand() % Max_X;
			for (j = 0; j < 8; j++)
			{
				if (abs(FindDupli[i] - FindDupli[j]) < 3)//만약 5칸 이내에 장애물이나 다른 보상이 있다면
				{
					FindDupli[i] = rand() % Max_X;//다시 설정함
					continue;
				}
			}
			Obje1->x = FindDupli[i];
			Obje1->y = 0;
			Obje1->speed = rand() % 10 + 1;
			return;
	}
//오브젝트 스피드가 1이 되는 것을 먹은 것의 기준으로 봄 
		gotoxy(Obje1->x, Obje1->y);
		for (j = 1 + i; j <= 2 + i; j++)
		{
			printf("%c", *(GoldText + j));
		}
		Obje1->y += Obje1->speed;
		return;
}//보상 문자열의 움직임을 제어
void PlayerMoveControl(ObjectCoord* Obje1)
{
	gotoxy(Obje1->x, Obje1->y);
	printf("   ");
	char ch = _getch();
	switch (ch)
	{
		case 75:
		{
			if(Obje1->x > 0)
				Obje1->x -= Obje1->speed;
			break;
		}
		case 77:
		{
			if (Obje1->x <= Max_X)
				Obje1->x += Obje1->speed;
			break;
		}
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("◇");
	return;
}
//여기까지
void Quiz()//퀴즈에서 문제가 나오고,문제를 풀면 됨. 이때 문자는 포인터 배열의 형태로 주어짐. 
{

}
