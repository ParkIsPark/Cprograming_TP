#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility ����Ǿ� ����.

///<PWminigame�� ���ǵ�> 

#define Password_Easy_Max_Len 2//���ڿ� ���̴� �׻� �ϳ� �� ���� ¥�ֱ�
#define Password_Easy_Max_end_time 10.0f
#define Password_Easy_Max_Hint 3

#define Password_Normal_Max_Len 5
#define Password_Normal_Max_end_time 10.0f
#define Password_Normal_Max_Hint 10.0f

#define Password_Hard_Max_Len 5
#define Password_Hard_Max_end_time 10.0f
#define Password_Hard_Max_Hint 10.0f
///<GetData�� ���ǵ�>
#define GetData_Max_X 70//GatData���ӿ��� x������ ������ ����


#define GetData_Easy_MAX_target 3
#define GetData_Easy_MAX_Obstacle 5

#define GetData_Normal_MAX_target 4
#define GetData_Normal_MAX_Obstacle 7

#define GetData_Hard_MAX_target 5
#define GetData_Hard_MAX_Obstacle 12//������ Ÿ�� ����, ���⼭ ���ݸ� �ٲ��ָ� ��.

#define GetData_Easy_hp 4
#define GetData_Easy_end_time 15.0f

#define GetData_Normal_hp 3
#define GetData_Normal_end_time 12.0f

#define GetData_Hard_hp 2
#define GetData_Hard_end_time 10.0f//������ �ð� ���.. 

#define GetData_Distance 5//���� �������ִ� ����
///</�������>


//�̴ϰ����� ��ü������ ����ϴ� ����ü�� ��������
typedef enum difficulty {//���̵� ���� ����. ���⼭ l �ϳ� ������.
	Easy,
	Normal,
	Hard
}difficulty;//���� 0, 1, 2�� ����, Easy, Normal, Hard ���� ������ �����ϰ� 0, 1, 2 ����ϸ� ��. 

typedef struct level_memory {//���� �ð��� hp. 
	float end_time;
	int hp;
}level_memory;
//

//�н�������ӿ� ����ü ����
typedef struct Password_inform {//�Ծ�� �ϴ� ��ǥ�� ������ ��� ��Ʈ����.. 
	size_t size;//����� ������ ���� �κ�
	char* pw;//�н����� ������ ���� �κ�
}Password_inform;
//

//GetData�� ����������
int* FindDupli;//������Ʈ ���� �ߺ� �ִ��� Ȯ�� /���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
typedef struct ObjectCoord//������Ʈ ��ǥ�� �����ص� ��Ʈ����
{
	int x;//x��
	int y;//y��
	int speed;//�ӵ�
}ObjectCoord;

typedef struct target {//�Ծ�� �ϴ� ��ǥ�� ������ ��� ��Ʈ����.. 
	char* name;
	size_t n;
}target;

 

//�Լ� ����� 

//�н����� �̴ϰ��ӿ� �Լ���
void PW_game_init(difficulty);
void PW_game(Password_inform*, level_memory*);//��й�ȣ ����. 
void PW_game_show_PW_screen(Password_inform*);//��Ʈ + �н����� �����ִ� ȭ��
void PW_game_show_input_screen(int, int);//��ǲȭ��
void PW_game_wIn();//�¸����� �� ����
void PW_game_show_winsreen();//�̰��� �� UI ������
void PW_game_defeat();//�й���� �� ����
void PW_game_show_defeatscreen();//���� �� ȭ�� ������

//�ٵ����Ϳ� �Լ���
void GetData_game_init(difficulty);//�ٵ����� ���� �ʱ�ȭ
void Getdata_Minigame(target*, level_memory*, int, int, int);//�������� �����͸� ���������� �ݴ� ����
void Control_Obst_Move(ObjectCoord*, int, ObjectCoord, int*, int, int);//�ٵ����Ϳ�, ������Ʈ���� ���� ��ġ ��Ʈ��
void Control_Target_Move(ObjectCoord*, target*, int, char*, int, ObjectCoord, char*, int, int);//���������Ʈ���� ��ġ ��Ʈ��
void Control_Player_Move(ObjectCoord*);//�÷��̾� ��ġ ��Ʈ��
void get_position(size_t, int, int);//���� ��ġ �ο�
void GetData_game_show_menu_screen(int, float, char*, int);//���� ���� ���
void GetData_game_show_Gameover_screen(int, int);//���� �� ȭ�� ���

//
int main()
{
	srand((unsigned)time(NULL));//���� ��������� ��. 
	GetData_game_init(Easy);
	printf("��");
	Sleep(2000);
	return 0;
}
void PW_game_init(difficulty difficult)
{
	Password_inform* Password = (Password_inform*)calloc(1, sizeof(Password_inform));//�н����� ������ ������ ����
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));//���� ���� �Ҵ��̶� ������ �ʱ�ȭ �������.
	switch (difficult) {
		case Easy://���̵� �Ҵ� �۾�
			Password->size = Password_Easy_Max_Len;
			(*Password).pw = (char*)calloc(Password_Easy_Max_Len, sizeof(char));
			Level->end_time = Password_Easy_Max_end_time;
			Level->hp = Password_Easy_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		case Normal:
			Password->size = Password_Normal_Max_Len;
			(*Password).pw = (char*)calloc(Password_Normal_Max_Len, sizeof(char));
			Level->end_time = Password_Normal_Max_end_time;
			Level->hp = Password_Normal_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		case Hard:
			Password->size = Password_Hard_Max_Len;
			(*Password).pw = (char*)calloc(Password_Hard_Max_Len, sizeof(char));
			Level->end_time = Password_Hard_Max_end_time;
			Level->hp = Password_Hard_Max_Hint;//���⼱ hp�� ��Ʈ
			break;
		default: 
			printf("�ùٸ� ���̵��� �������ּ���");
			return;
			break;

	}
	PW_game(Password, Level);//�޸� ���� Ȯ���ϴ� ���� �־��ֱ�
}
void PW_game(Password_inform* Password, level_memory* Level)
{
	int i, j = 0;
	int Hint_amount = Level->hp;//��Ʈ ����
	int end_time = (int)Level->end_time; //���� end time ��� �����ϴٸ� ����� ��.. ���⼱ ��� ��� ���� �𸣰ڴ�.
	int s_time;
	char* Password_pw = (*Password).pw;
	char* initialize = (char*)calloc(Password->size, sizeof(char));//�ʱ�ȭ�� ����
	char* input = (char*)calloc(Password->size, sizeof(char));//����� �Է� �޴� ����. �� �� �����Ҵ��̶� free �������
	//��й�ȣ ���� ����
	for (i = 0; i < (Password->size)-1; i++)//�н����� �Ҵ� �۾�
	{
		if (rand() % 2)
			Password_pw[i] = 'a' + rand() % 26;

		else
			Password_pw[i] = 'A' + rand() % 26;

	}
	Password_pw[i] = '\0';
	//
	PW_game_show_PW_screen(Password);//���� ���� ȭ�� ���
	PW_game_show_input_screen(Hint_amount, end_time);//��ǲ ȭ�� ���
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
		if (j >= Password->size - 1) {//�� �Է����� ���
			input[Password->size - 1] = '\0';
			printf("\n�˻���..."); 
			Sleep(2000);
			if (!strcmp(Password->pw, input)){
				PW_game_wIn();
				break;
			}
			else {
				if (Hint_amount > 0) {
					system("cls");
					Hint_amount--;
					printf("\n Ʋ�Ƚ��ϴ�, ���� ��Ʈ�� %d���Դϴ�.", Hint_amount);
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
		free(Password); //�����Ҵ� ����
		free(Level); 
		free(initialize); 
		free(input);
	}
}
void PW_game_show_PW_screen(Password_inform* Password)//�н����� �̴ϰ��ӿ��� ��й�ȣ �Է� ȭ�� ����ϴ� ��
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|           ��й�ȣ: %s                           |\n", (*Password).pw);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
void PW_game_show_input_screen(int hp, int end_time)//����� �Է� �޴� ��ũ��
{
	system("cls");
	printf("----------------------------------------------------------\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|    ��й�ȣ�� �Է��ϼ���                                |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	printf("���� ��ȸ : %d\n", hp, end_time); 
	return;
}
void PW_game_wIn()
{
	PW_game_show_winsreen();
	//���� ���⿡ ���� ��
}
void PW_game_show_winsreen()
{
	system("cls");
	printf("�����մϴ�! ������ Ŭ�����ϼ̽��ϴ�!");
	Sleep(2000);
}
void PW_game_defeat()
{
	PW_game_show_defeatscreen();
	//���� ���⿡ ����� ��
}
void PW_game_show_defeatscreen()
{
	system("cls");
	printf("�� �����մϴ�! ������ �� Ŭ�����ϼ̽��ϴ�!");
	Sleep(2000);
}

//getdata �̴ϰ���
void GetData_game_init(difficulty difficult) {//���̵��� ���� �� ���ڵ�� hp, ������ �ð�. Easy�� 0��, Normal�� 1��, Hard�� 2����. 
	target* Target = (target*)calloc(1, sizeof(target));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	level_memory* Level = (level_memory*)calloc(1, sizeof(level_memory));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	int IsProperDiff = 0;//���̵��� �ùٸ��� Ȯ����.
	int Targetamount, Obstacleamount;
	switch(difficult)//Ease, Normal, Hard�� ���� 0,1,2�� �ش��ϰ� �����Ǳ� ������ ��������. ���̵��� ���� �ٸ� ���� ����.
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
			printf("�ùٸ� ���̵��� �������ּ���");
			return;
			break;
	}
	if (IsProperDiff)
	{
		if (FindDupli == NULL)//�����Ҵ� ���� üũ
		{
			printf("\n\n���� : �޸𸮰� �����մϴ�"); 
			return;
		}
		else
		{
			Getdata_Minigame(Target, Level, difficult, Targetamount, Obstacleamount);
			return;
		}
	}
}
void Getdata_Minigame(target* Target, level_memory* Stats, int difficult, int targetamount, int obstacleamount)//���� ����� [����], ����� �迭�� �ݴ� ����. 
{
	int GameHp = Stats->hp;//���� ü��
	float GameOverCount = Stats->end_time;//���� ������ �ð�
	int string_size = (int)Target->n;
	char *GetData = (char*)calloc((((int)Target->n)+1), sizeof(char));
	GetData[(Target->n)+1] = '\0';//������ ���ڿ� ����Ǵ� �迭. �����Ҵ���(free�� ����)
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//Ÿ�� ���� ����Ǵ� �迭
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//��ֹ� ���� ����Ǵ� �迭
	ObjectCoord P1 = { 0, 29, 3 };//�÷��̾� ����
	int IsFullCollect = 0;//���� ��Ҵ��� Ȯ���ϴ� ����. 
	int i;//�ݺ����� ����
	int arr_size = (obstacleamount+targetamount)/sizeof(int);//�迭 ������ 
	for (i = 0; i < obstacleamount; i++)//��ǥ�� �ο����ִ� ����.
	{
		get_position(arr_size, i, string_size/targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount+targetamount; i++)//���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		get_position(arr_size, i, string_size);
		D[i-obstacleamount].x = FindDupli[obstacleamount];//D�� B�� ���� �迭�� �޶��. 
		D[i-obstacleamount].y = 0;
		D[i-obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//ȭ�� �����

		if (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
		{
			Control_Player_Move(&P1);
		}
		for (i = 0; i < obstacleamount; i++) {//������Ʈ �������ִ� ����
			Control_Obst_Move(&B[i], i, P1, &GameHp, arr_size, string_size);
		}
		for (i = 0; i < targetamount; i++)
		{
			if (D[i].speed != -1)
			{
				Control_Target_Move(&D[i], Target, 2 * i, Target->name, arr_size, P1, GetData, arr_size, string_size);//�̸��� ����.
			}
		}
		if (GameHp <= 0 || GameOverCount <= 0)//���� ���� �ڵ�. �������� �� �������� �ѹ� üũ����. 
		{
			break;
		}
		if (_kbhit())
		{
			Control_Player_Move(&P1);
		}
//ȭ�� ����� �ڵ�
		GetData_game_show_menu_screen(GameHp, GameOverCount, GetData, string_size);
		if (strlen(GetData) >= string_size-1)//���߿� ���⼭ ���� �� ����, üũ
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
		if (_kbhit())//�÷��̾� ��ġ�� ��� üũ���ָ鼭 ������ �ؼ�
		{
			Control_Player_Move(&P1);
		}
		GameOverCount -= 0.2f;

	}//���� �ڵ�
	system("cls");
	IsFullCollect = 0;
	for (i = 0; i < string_size; i++)
	{
		if (GetData[i] == Target->name[i + 1])//�ν�Ʈ
		{
			IsFullCollect += 1;
		}
	}
	GetData_game_show_Gameover_screen(IsFullCollect, string_size);
	//���� �׼�(�޸� �Ҵ� ����)
	free(Target);
	free(Stats);
	free(FindDupli);
}
void Control_Obst_Move(ObjectCoord* Obje1, int i, ObjectCoord Player, int* Hp, int Allamount, int string_size)//������Ʈ �������� ���
{
	int j = 0;//���⼭�� ���Ǵ� ��������
	if (Obje1->y >= 30)//������ �� �� ����
	{
		if (abs(Player.x - Obje1->x) < 5)//hp���� ����
		{
			(*Hp)--;
		}
		gotoxy(Obje1->x, Obje1->y - 1);//���� ����
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
}//�� ������ ����
void Control_Target_Move(
	ObjectCoord* Obje1, target* Target, 
	int i, char* TargetText, int arr_size,
	ObjectCoord Player, char* GetText, int Targetamount, int string_size)
{
	int t = 0;//�ؿ�.. ���� �������� ����ϴ¤���
	int j = 0;//���⼭�� ���Ǵ� ��������
	if (Obje1->y >= 30)//������ �� �� ����
	{
		if (abs(Player.x - Obje1->x) < Target->n/Targetamount)//��Ҵ��� Ȯ���ϴ� ����
		{
			t = i;
			for (j = 1 + i; j <= 2 + i; j++)
			{
				GetText[t] = TargetText[j];
				t++;
			}
			Obje1->speed = -1;
			gotoxy(Obje1->x, Obje1->y - 1);//���� ����
			printf("     ");
			Obje1->y = 0;
			return;
		}
		gotoxy(Obje1->x, Obje1->y - 1);//���� ����
		printf("     ");
		get_position(arr_size, i, ((int)Target->n / Targetamount + 3));
		Obje1->x = FindDupli[i];
		Obje1->y = 0;
		Obje1->speed = rand() % 10 + 1;
		return;
	}
	//������Ʈ ���ǵ尡 1�� �Ǵ� ���� ���� ���� �������� �� 
	gotoxy(Obje1->x, Obje1->y);
	for (j = 1 + i; j <= 2 + i; j++)
	{
		printf("%c", *(TargetText + j));
	}
	Obje1->y += Obje1->speed;
	return;
}//���� ���ڿ��� �������� ����
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
	printf("��");
	return;
}
void get_position(size_t size, int idx, int distance) {//��ġ ����ִ� ����, ��ֹ��� �����, ������Ʈ ��ȣ, ���� ���� �޾Ƽ� ��ġ ����.
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		if (abs(pos - FindDupli[i]) < distance+3)//���� 3ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
		{
			pos = rand() % GetData_Max_X;//�ٽ� ������
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
		printf("|");//30�� �ݺ��ϸ鼭 y�� �������� �� ���� �����ִ� ���Դϴ�. 
	}
	gotoxy(GetData_Max_X + 13, 5);
	printf("�������� �����͸� �ֿ켼��!");
	gotoxy(GetData_Max_X + 13, 8);
	printf("���� ü�� : %d", GameHp);
	gotoxy(GetData_Max_X + 13, 12);
	printf("���� �ð� : %.f", GameOverCount);
	gotoxy(GetData_Max_X + 13, 15);//�������� �ܼ��� ����Ԉ�.
	printf("���ݱ��� �ֿ� �迭 : ");
	for (i = 0; i < string_size; i++)
	{
		printf("%c", GetData[i]);//���ݱ��� �ֿ� �迭�� ����մϴ�.
	}
}
void GetData_game_show_Gameover_screen(int IsFullCollect, int string_size){
	printf("----------------------------------------------------------\n");//ȭ�� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      �Ϸ��� = %.lf%%                        |\n", ((float)IsFullCollect / string_size) * 100);//�Ϸ����� ������� �ؼ� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
}
//�������

