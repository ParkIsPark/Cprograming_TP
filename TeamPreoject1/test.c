#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility 저장되어 있음.

///<PWminigame용 정의들> 

#define Password_Easy_Max_Len 2//문자열 길이는 항상 하나 더 많게 짜주기
#define Password_Easy_Max_end_time 10.0f
#define Password_Easy_Max_Hint 3

#define Password_Normal_Max_Len 5
#define Password_Normal_Max_end_time 10.0f
#define Password_Normal_Max_Hint 10.0f

#define Password_Hard_Max_Len 5
#define Password_Hard_Max_end_time 10.0f
#define Password_Hard_Max_Hint 10.0f
///<GetData용 정의들>
#define GetData_Max_X 70//GatData게임에서 x축으로 퍼지는 정도


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 4
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 5
#define GetData_Hard_MAX_Obstacle 12//내려올 타켓 개수, 여기서 조금만 바꿔주면 됨.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
#define GetData_Hard_end_time 10.0f//끝나는 시간 등등.. 

#define GetData_Distance 5//서로 떨어져있는 정도
///</여기까지>


//미니게임이 전체적으로 사용하는 구조체와 열거형들
typedef enum difficulty {//난이도 설정 변수. 여기서 l 하나 지웠음.
	Easy,
	Normal,
	Hard
}difficulty;//각자 0, 1, 2에 대응, Easy, Normal, Hard 쓰고 싶으면 스근하게 0, 1, 2 사용하면 됨. 

typedef struct level_memory {//종료 시간과 hp. 
	float end_time;
	int hp;
}level_memory;
//

//패스워드게임용 구조체 정의
typedef struct Password_inform {//먹어야 하는 목표의 정보가 담긴 스트럭쳐.. 
	size_t size;//사이즈가 실제로 들어가는 부분
	char* pw;//패스워드 실제로 들어가는 부분
}Password_inform;
//

//GetData용 전역변수들
int* FindDupli;//오브젝트 값에 중복 있는지 확인 /동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
typedef struct ObjectCoord//오브젝트 좌표값 저장해둘 스트럭쳐
{
	int x;//x값
	int y;//y값
	int speed;//속도
}ObjectCoord;

typedef struct target {//먹어야 하는 목표의 정보가 담긴 스트럭쳐.. 
	char* name;
	size_t n;
}target;

 

//함수 선언들 

//패스워드 미니게임용 함수들
void PW_game_init(difficulty);
void PW_game(Password_inform*, level_memory*);//비밀번호 게임. 
void PW_game_show_PW_screen(Password_inform*);//힌트 + 패스워드 보여주는 화면
void PW_game_show_input_screen(int, int);//인풋화면
void PW_game_wIn();//승리했을 때 동작
void PW_game_show_winsreen();//이겼을 때 UI 디자인
void PW_game_defeat();//패배앴을 때 동작
void PW_game_show_defeatscreen();//졌을 때 화면 디자인

//겟데이터용 함수들
void GetData_game_init(difficulty);//겟데이터 게임 초기화
void Getdata_Minigame(target*, level_memory*, int, int, int);//떨어지는 데이터를 성공적으로 줍는 게임
void Control_Obst_Move(ObjectCoord*, int, ObjectCoord, int*, int, int);//겟데이터용, 오브젝트들의 현재 위치 컨트롤
void Control_Target_Move(ObjectCoord*, target*, int, char*, int, ObjectCoord, char*, int, int);//보상오브젝트들의 위치 컨트롤
void Control_Player_Move(ObjectCoord*);//플레이어 위치 컨트롤
void get_position(size_t, int, int);//랜덤 위치 부여
void GetData_game_show_menu_screen(int, float, char*, int);//게임 시작 출력
void GetData_game_show_Gameover_screen(int, int);//게임 끝 화면 출력

//
int main()
{
	srand((unsigned)time(NULL));//랜덤 정의해줘야 함. 
	GetData_game_init(Easy);
	printf("끝");
	Sleep(2000);
	return 0;
}
void PW_game_init(difficulty difficult)
{
	Password_inform* Password = (Password_inform*)calloc(1, sizeof(Password_inform));//패스워드 저장할 포인터 선언
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));//전부 동적 할당이라서 무조건 초기화 해줘야함.
	switch (difficult) {
		case Easy://난이도 할당 작업
			Password->size = Password_Easy_Max_Len;
			(*Password).pw = (char*)calloc(Password_Easy_Max_Len, sizeof(char));
			Level->end_time = Password_Easy_Max_end_time;
			Level->hp = Password_Easy_Max_Hint;//여기선 hp가 힌트
			break;
		case Normal:
			Password->size = Password_Normal_Max_Len;
			(*Password).pw = (char*)calloc(Password_Normal_Max_Len, sizeof(char));
			Level->end_time = Password_Normal_Max_end_time;
			Level->hp = Password_Normal_Max_Hint;//여기선 hp가 힌트
			break;
		case Hard:
			Password->size = Password_Hard_Max_Len;
			(*Password).pw = (char*)calloc(Password_Hard_Max_Len, sizeof(char));
			Level->end_time = Password_Hard_Max_end_time;
			Level->hp = Password_Hard_Max_Hint;//여기선 hp가 힌트
			break;
		default: 
			printf("올바른 난이도를 선택해주세요");
			return;
			break;

	}
	PW_game(Password, Level);//메모리 찬거 확인하는 로직 넣어주기
}
void PW_game(Password_inform* Password, level_memory* Level)
{
	int i, j = 0;
	int Hint_amount = Level->hp;//힌트 개수
	int end_time = (int)Level->end_time; //만약 end time 사용 가능하다면 사용할 것.. 여기선 어떻게 써야 할지 모르겠다.
	int s_time;
	char* Password_pw = (*Password).pw;
	char* initialize = (char*)calloc(Password->size, sizeof(char));//초기화용 변수
	char* input = (char*)calloc(Password->size, sizeof(char));//사용자 입력 받는 변수. 둘 다 동적할당이라 free 해줘야함
	//비밀번호 설정 과정
	for (i = 0; i < (Password->size)-1; i++)//패스워드 할당 작업
	{
		if (rand() % 2)
			Password_pw[i] = 'a' + rand() % 26;

		else
			Password_pw[i] = 'A' + rand() % 26;

	}
	Password_pw[i] = '\0';
	//
	PW_game_show_PW_screen(Password);//게임 시작 화면 출력
	PW_game_show_input_screen(Hint_amount, end_time);//인풋 화면 출력
	s_time = time(0);
	//
	while (1) {

		if (_kbhit())
		{
			if ((input[j] = _getch()) == 8)
			{
				if (j == 0)
					continue;
				j--;
				printf("\b \b");
				input[j] = '\0';
			}

			else
			{
				printf("%c", input[j]);
				j++;
			}
		}
		if (j >= Password->size - 1) {//다 입력했을 경우
			input[Password->size - 1] = '\0';
			printf("\n검사중..."); 
			Sleep(2000);
			if (!strcmp(Password->pw, input)){
				PW_game_wIn();
				break;
			}
			else {
				if (Hint_amount > 0) {
					system("cls");
					Hint_amount--;
					printf("\n 틀렸습니다, 남은 힌트는 %d개입니다.", Hint_amount);
					Sleep(2000);
					j = 0;
					strcpy(input, initialize);
					PW_game_show_PW_screen(Password);
					PW_game_show_input_screen(Hint_amount, end_time);
				}
				else {
					PW_game_defeat();
					break;
				}
			}
		}
		free(Password); //동적할당 해제
		free(Level); 
		free(initialize); 
		free(input);
	}
}
void PW_game_show_PW_screen(Password_inform* Password)//패스워드 미니게임에서 비밀번호 입력 화면 출력하는 것
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|           비밀번호: %s                           |\n", (*Password).pw);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
void PW_game_show_input_screen(int hp, int end_time)//사용자 입력 받는 스크린
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|    비밀번호를 입력하세요                                |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	printf("남은 기회 : %d\n", hp, end_time); 
	return;
}
void PW_game_wIn()
{
	PW_game_show_winsreen();
	//이후 여기에 버프 들어감
}
void PW_game_show_winsreen()
{
	system("cls");
	printf("축하합니다! 게임을 클리어하셨습니다!");
	Sleep(2000);
}
void PW_game_defeat()
{
	PW_game_show_defeatscreen();
	//이후 여기에 디버프 들어감
}
void PW_game_show_defeatscreen()
{
	system("cls");
	printf("안 축하합니다! 게임을 못 클리어하셨습니다!");
	Sleep(2000);
}

//getdata 미니게임
void GetData_game_init(difficulty difficult) {//난이도에 따라 들어갈 문자들과 hp, 끝나는 시간. Easy는 0번, Normal은 1번, Hard는 2번임. 
	target* Target = (target*)calloc(1, sizeof(target));////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));////동적 할당임. 만약 힙 메모리 부족 뜬다면 이거 초기화했는지 다시 확인해보기
	int IsProperDiff = 0;//난이도가 올바른지 확인함.
	int Targetamount, Obstacleamount;
	switch(difficult)//Ease, Normal, Hard는 각각 0,1,2에 해당하게 번역되기 떄문에 문제없음. 난이도에 따라 다른 상태 지정.
	{
		case Easy:
			Target->name = " Kimch!";
			Target->n = 6;
			FindDupli = (int*)malloc((GetData_Easy_MAX_target + GetData_Easy_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Easy_hp;
			Level->end_time = GetData_Easy_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Easy_MAX_target;
			Obstacleamount = GetData_Easy_MAX_Obstacle;
			break;
		case Normal: 
			Target->name = " Kimch!";
			Target->n = 6;
			FindDupli = (int*)malloc((GetData_Normal_MAX_target + GetData_Normal_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Normal_hp;
			Level->end_time = GetData_Normal_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Normal_MAX_target;
			Obstacleamount = GetData_Normal_MAX_Obstacle;
			break;
		case Hard:
			Target->name = " HelloPlayer!";
			Target->n = 12;
			FindDupli = (int*)malloc((GetData_Hard_MAX_target + GetData_Hard_MAX_Obstacle) * sizeof(int));
			Level->hp = GetData_Hard_hp;
			Level->end_time = GetData_Hard_end_time;
			IsProperDiff = 1;
			Targetamount = GetData_Hard_MAX_target;
			Obstacleamount = GetData_Hard_MAX_Obstacle;
			break;
		default:
			printf("올바른 난이도를 선택해주세요");
			return;
			break;
	}
	if (IsProperDiff)
	{
		if (FindDupli == NULL)//동적할당 오류 체크
		{
			printf("\n\n에러 : 메모리가 부족합니다"); 
			return;
		}
		else
		{
			Getdata_Minigame(Target, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}
}
void Getdata_Minigame(target* Target, level_memory* Stats, int difficult, int targetamount, int obstacleamount)//상자 모양은 [문자], 흩어진 배열을 줍는 게임. 
{
	int GameHp = Stats->hp;//게임 체력
	float GameOverCount = Stats->end_time;//게임 끝나는 시간
	int string_size = (int)Target->n;
	char *GetData = (char*)calloc((((int)Target->n)+1), sizeof(char));
	GetData[(Target->n)+1] = '\0';//떨어진 문자열 저장되는 배열. 동적할당임(free를 쓰라)
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//타겟 정보 저장되는 배열
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//장애물 정보 저장되는 배열
	ObjectCoord P1 = { 0, 29, 3 };//플레이어 변수
	int IsFullCollect = 0;//전부 모았는지 확인하는 변수. 
	int i;//반복문용 변수
	int arr_size = (obstacleamount+targetamount)/sizeof(int);//배열 사이즈 
	for (i = 0; i < obstacleamount; i++)//좌표값 부여해주는 과정.
	{
		get_position(arr_size, i, string_size/targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount+targetamount; i++)//보상 위치를 중복 없게끔 만들어주는 함수
	{
		get_position(arr_size, i, string_size);
		D[i-obstacleamount].x = FindDupli[obstacleamount];//D랑 B랑 서로 배열이 달라요. 
		D[i-obstacleamount].y = 0;
		D[i-obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//화면 비워줌

		if (_kbhit())//시분할로 코드를 구성함. 첫번째로는 플레이어 움직임을 컨트롤함.
		{
			Control_Player_Move(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//오브젝트 움직여주는 과정
			Control_Obst_Move(&B[i], i, P1, &GameHp, arr_size, string_size);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				Control_Target_Move(&D[i], Target, 2 * i, Target->name, arr_size, P1, GetData, arr_size, string_size);//이름이 간다.
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//게임 종료 코드. 내려왔을 때 기준으로 한번 체크해줌. 
		{
			break;
		}
		if (_kbhit())
		{
			Control_Player_Move(&P1);
		}
//화면 만드는 코드
		GetData_game_show_menu_screen(GameHp, GameOverCount, GetData, string_size);
		if (strlen(GetData) >= string_size-1)//나중에 여기서 오류 날 수도, 체크
		{
			break;
		}
		gotoxy(P1.x, P1.y);
		for (i = 0; i < 4; i++)
		{
			while(_kbhit())
			{
				Control_Player_Move(&P1);
			}
			Sleep(50);
		}
		if (_kbhit())//플레이어 위치를 계속 체크해주면서 딜레이 해소
		{
			Control_Player_Move(&P1);
		}
		GameOverCount -= 0.2f;

	}//게임 코드
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < string_size; i++)
	{
		if (GetData[i] == Target->name[i + 1])//로스트
		{
			IsFullCollect += 1;
		}
	}
	GetData_game_show_Gameover_screen(IsFullCollect, string_size);
	//프리 액션(메모리 할당 해제)
	free(Target);
	free(Stats);
	free(FindDupli);
}
void Control_Obst_Move(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp, int Allamount, int string_size)//오브젝트 움직임을 담당
{
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < 5)//hp감소 로직
		{
			(*Hp)--;
		}
		gotoxy(Obje1->x, Obje1->y - 1);//삭제 로직
		printf(" ");
		get_position(Allamount, i, string_size);
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
void Control_Target_Move(
	ObjectCoord* Obje1, target* Target, 
	int i, char* TargetText, int arr_size,
	ObjectCoord Player, char* GetText, int Targetamount, int string_size)
{
	int t = 0;//밑에.. 대충 뭔가에서 사용하는ㄱ것
	int j = 0;//여기서만 사용되는 지역변수
	if (Obje1->y >= 30)//끝까지 간 별 삭제
	{
		if (abs(Player.x - Obje1->x) < Target->n/Targetamount)//닿았는지 확인하는 로직
		{
			t = i;
			for (j = 1 + i; j <= 2 + i; j++)
			{
				GetText[t] = TargetText[j];
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
		get_position(arr_size, i, ((int)Target->n / Targetamount + 3));
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	//오브젝트 스피드가 1이 되는 것을 먹은 것의 기준으로 봄 
	gotoxy(Obje1->x, Obje1->y);
	for (j = 1 + i; j <= 2 + i; j++)
	{
		printf("%c", *(TargetText + j));
	}
	Obje1->y += Obje1->speed;
	return;
}//보상 문자열의 움직임을 제어
void Control_Player_Move(ObjectCoord* Obje1)
{
	gotoxy(Obje1->x, Obje1->y);
	printf("   ");
	char ch = _getch();
	switch (ch)
	{
	case 75:
	{
		if (Obje1->x > 0)
			Obje1->x -= Obje1->speed;
		break;
	}
	case 77:
	{
		if (Obje1->x <= GetData_Max_X)
			Obje1->x += Obje1->speed;
		break;
	}
	}
	gotoxy(Obje1->x, Obje1->y);
	printf("◇");
	return;
}
void get_position(size_t size, int idx, int distance) {//위치 담겨있는 변수, 장애물이 몇개인지, 오브젝트 번호, 글자 길이 받아서 위치 설정.
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //보상 위치를 중복 없게끔 만들어주는 함수
	{
		if (abs(pos - FindDupli[i]) < distance+3)//만약 3칸 이내에 장애물이나 다른 보상이 있다면
		{
			pos = rand() % GetData_Max_X;//다시 설정함
			i = 0;
		}
	}
	FindDupli[idx] = pos;
}
void GetData_game_show_menu_screen(int GameHp, float GameOverCount, char* GetData, int string_size)
{
	int i = 0;
	for (i = 0; i < 30; i++)
	{
		gotoxy(GetData_Max_X + 10, i);
		printf("|");//30번 반복하면서 y축 기준으로 저 벽을 세워주는 것입니다. 
	}
	gotoxy(GetData_Max_X + 13, 5);
	printf("떨어지는 데이터를 주우세요!");
	gotoxy(GetData_Max_X + 13, 8);
	printf("남은 체력 : %d", GameHp);
	gotoxy(GetData_Max_X + 13, 12);
	printf("남은 시간 : %.f", GameOverCount);
	gotoxy(GetData_Max_X + 13, 15);//나머지는 단순한 출력입닏.
	printf("지금까지 주운 배열 : ");
	for (i = 0; i < string_size; i++)
	{
		printf("%c", GetData[i]);//지금까지 주운 배열을 출력합니다.
	}
}
void GetData_game_show_Gameover_screen(int IsFullCollect, int string_size){
	printf("----------------------------------------------------------\n");//화면 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      완료율 = %.lf%%                        |\n", ((float)IsFullCollect / string_size) * 100);//완료율을 백분위로 해서 출력
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
//여기까지

