#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "GameUtility.h"//GameUtility ����Ǿ� ����.



///<PWminigame�� ���ǵ�> 

#define Passward_Easy_Max_Len 5
#define Passward_Easy_Max_end_time 10.0f
#define Passward_Easy_Max_Hint 10.0f

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


//���α׷��� ��ü������ ����ϴ� ����ü�� ��������

typedef enum difficullty {//���̵� ���� ����.
	Easy,
	Normal,
	Hard
}difficulty;//���� 0, 1, 2�� ����, Easy, Normal, Hard ���� ������ �����ϰ� 0, 1, 2 ����ϸ� ��. 

typedef struct level_memory {//���� �ð��� hp. 
	float end_time;
	int hp;
}level_memory;
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
void PW_game(int);//��й�ȣ ����. 

//�ٵ����Ϳ� �Լ���
void GetData_game_init(difficulty);//�ٵ����� ���� �ʱ�ȭ
void Getdata_Minigame(target*, level_memory*, int, int, int);//�������� �����͸� ���������� �ݴ� ����
void Control_Obst_Move(ObjectCoord*, int, ObjectCoord, int*, int, int);//�ٵ����Ϳ�, ������Ʈ���� ���� ��ġ ��Ʈ��
void Control_Target_Move(ObjectCoord*, target*, int, char*, int, ObjectCoord, char*, int, int);//���������Ʈ���� ��ġ ��Ʈ��
void Control_Player_Move(ObjectCoord*);//�÷��̾� ��ġ ��Ʈ��
void get_position(size_t, int, int);//���� ��ġ �ο�
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
	char* Password;//�н����� ������ ������ ����
	switch (difficult) {
	case Easy:
		Password = (char*)calloc(Passward_Easy_Max_Len, sizeof(char));
		break;

	}

}
void PW_Game(int Difficult)
{
	srand((unsigned)time(NULL));
	char word[10];
	char input[10];
	int TryLimit, i;//�ݺ��� ����� ����, TryLimit�� ��й�ȣ ����
	TryLimit = Difficult;
	//��й�ȣ ����
	for (i = 0; i < 9; i++)
	{
		word[i] = 'a' + rand() % 25;
	}
	word[i] = '\0';
	//��й�ȣ ����
	//
	for (; TryLimit > 0; TryLimit--)//���̵��� ���� �־����� Ƚ����ŭ ����
	{
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|           ��й�ȣ: %s                           |\n", word);
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		Sleep(2000);
		system("cls");
		//
		//��й�ȣ �Է� �޴� ������
		printf("----------------------------------------------------------\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|    ��й�ȣ�� �Է��ϼ���                                |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("----------------------------------------------------------\n");
		printf(":");
		gets_s(input, 10);//���߿� ���� ����Ʈ�� �ٲٱ�. 
		///
		///����, ���� ���� �ǰ���
		if (!(strcmp(word, input)))
		{
			printf("�����Դϴ�.");
			//hp���� ����� Ư�� �� �ڸ�
			// //������ ����
		}
		else
		{
			if (TryLimit - 1)//�õ� Ƚ�� �����ִ��� Ȯ��
			{
				printf("Ʋ�Ƚ��ϴ�. ��ȸ�� %d���Դϴ�", TryLimit - 1);//Ʋ���� �ٽ� �ݺ�
				Sleep(2000);
				system("cls");
			}
			else
			{
				printf("��ȸ�� ��� �����ϼ̽��ϴ�. ������� �޽��ϴ�");
				//����� �ڵ�
			}
		}
	}
}



//getdata �̴ϰ���
void GetData_game_init(difficulty difficult) {//���̵��� ���� �� ���ڵ�� hp, ������ �ð�. Easy�� 0��, Normal�� 1��, Hard�� 2����. 
	target* Target = Target = (target*)calloc(1, sizeof(target));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	level_memory* Level = Level = (level_memory*)calloc(1, sizeof(level_memory));////���� �Ҵ���. ���� �� �޸� ���� ��ٸ� �̰� �ʱ�ȭ�ߴ��� �ٽ� Ȯ���غ���
	int IsProperDiff = 0;//���̵��� �ùٸ��� Ȯ����.
	int Targetamount, Obstacleamount;
	switch (difficult)//Ease, Normal, Hard�� ���� 0,1,2�� �ش��ϰ� �����Ǳ� ������ ��������. ���̵��� ���� �ٸ� ���� ����.
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
	char* GetData = (char*)calloc((((int)Target->n) + 1), sizeof(char));//������ ���ڿ� ����Ǵ� �迭. �����Ҵ���(free�� ����)
	ObjectCoord* D = (ObjectCoord*)malloc(targetamount * sizeof(ObjectCoord));//Ÿ�� ���� ����Ǵ� �迭
	ObjectCoord* B = (ObjectCoord*)malloc(obstacleamount * sizeof(ObjectCoord));//��ֹ� ���� ����Ǵ� �迭
	ObjectCoord P1 = { 0, 29, 3 };//�÷��̾� ����
	int IsFullCollect = 0;//���� ��Ҵ��� Ȯ���ϴ� ����. 
	int i;//�ݺ����� ����
	int arr_size = (obstacleamount + targetamount) / sizeof(int);//�迭 ������ 
	for (i = 0; i < obstacleamount; i++)//��ǥ�� �ο����ִ� ����.
	{
		get_position(arr_size, i, string_size / targetamount);
		B[i].x = FindDupli[i];
		B[i].speed = rand() % 10 + 1;
		B[i].y = 0;
	}
	for (i = obstacleamount; i < obstacleamount + targetamount; i++)//���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		get_position(arr_size, i, string_size);
		D[i - obstacleamount].x = FindDupli[obstacleamount];//D�� B�� ���� �迭�� �޶��. 
		D[i - obstacleamount].y = 0;
		D[i - obstacleamount].speed = rand() % 10 + 1;
	}
	while (1)
	{
		system("cls");//ȭ�� �����
		int cnt = 0;
		while (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
		{
			char ch = _getch();
			if (ch == 75) cnt--;
			else if (ch == 77) cnt++;
		}
		if(cnt) Control_Player_Move(&P1,cnt),cnt =0;
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
		//ȭ�� ����� �ڵ�
		for (i = 0; i < 30; i++)
		{
			gotoxy(GetData_Max_X + 10, i);
			printf("|");
		}
		gotoxy(GetData_Max_X + 13, 5);
		printf("�������� �����͸� �ֿ켼��!");
		gotoxy(GetData_Max_X + 13, 8);
		printf("���� ü�� : %d", GameHp);
		gotoxy(GetData_Max_X + 13, 12);
		printf("���ݱ��� �ֿ� �迭 : ");
		for (i = 0; i < string_size; i++)
		{
			printf("%c", GetData[i]);
			if (GetData[i] == Target->name[i + 1])
			{
				IsFullCollect += 1;
			}
		}
		if (IsFullCollect >= string_size - 1)
		{
			break;
		}
		IsFullCollect = 0;
		gotoxy(GetData_Max_X + 13, 15);
		printf("���� �ð� : %.f", GameOverCount);
		gotoxy(P1.x, P1.y);
		while (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
		{
			char ch = _getch();
			if (ch == 75) cnt--;
			else if (ch == 77) cnt++;
		}
		if (cnt) Control_Player_Move(&P1, cnt), cnt = 0;
		Sleep(200);
		/*
		for (i = 0; i < 4; i++)
		{
			while (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
			{
				char ch = _getch();
				if (ch == 75) cnt--;
				else if (ch == 77) cnt++;
			}
			if(cnt) Control_Player_Move(&P1,cnt);
			Sleep(50);
		}
		*/
		while (_kbhit())//�ú��ҷ� �ڵ带 ������. ù��°�δ� �÷��̾� �������� ��Ʈ����.
		{
			char ch = _getch();
			if (ch == 75) cnt--;
			else if (ch == 77) cnt++;
		}
		if (cnt) Control_Player_Move(&P1, cnt), cnt = 0;
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
	printf("----------------------------------------------------------\n");//ȭ�� ���
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("|                       GameOver                          |\n");
	printf("|                      �Ϸ��� = %.lf%%                        |\n", ((float)IsFullCollect / string_size) * 100);
	printf("|                                                         |\n");
	printf("|                                                         |\n");
	printf("----------------------------------------------------------\n");
	Sleep(2000);
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
		if (abs(Player.x - Obje1->x) < Target->n / Targetamount)//��Ҵ��� Ȯ���ϴ� ����
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
void Control_Player_Move(ObjectCoord* Obje1,int val)
{
	gotoxy(Obje1->x, Obje1->y);
	printf("   ");
	Obje1->x += val * Obje1->speed;
	gotoxy(Obje1->x, Obje1->y);
	printf("��");
	return;
}
void get_position(size_t size, int idx, int distance) {//��ġ ����ִ� ����, ��ֹ��� �����, ������Ʈ ��ȣ, ���� ���� �޾Ƽ� ��ġ ����.
	int i;
	int pos = rand() % GetData_Max_X;

	for (i = 0; i < size; i++) //���� ��ġ�� �ߺ� ���Բ� ������ִ� �Լ�
	{
		if (abs(pos - FindDupli[i]) < distance + 3)//���� 3ĭ �̳��� ��ֹ��̳� �ٸ� ������ �ִٸ�
		{
			pos = rand() % GetData_Max_X;//�ٽ� ������
			i = 0;
		}
	}
	FindDupli[idx] = pos;
}
//�������
