#include "Maingame_header.h"



#define Easy_flags_amount 3
#define Easy_falseflage_amount 2//��� ����� ����
#define Easy_Map_Max_x 20
#define Easy_Map_Max_y 10




int MAX_X = 20, MAX_Y = 10, FLAGS_T = 1, FLAGS_F = 2; // ���� ���̵� ���� ���� �ִ� ũ��, �Ϲ�, ���Ƽ ����� ����


typedef struct Obje_Coord {//���� �ð��� hp. 
	int x; 
	int y;
}Obje_coord;

//������ ����
typedef enum difficultyy {
	Easy,///���� 0, 1, 2�� �����մϴ�
	Normal,
	Hard
}Gamedifficulty;


int locate_flags_f[BASE][2]; // ���Ƽ ����� ������ (x, y) ��ǥ�� �����ϴ� �迭
int locate_flags_t[BASE][2]; // �Ϲ� ����� ������ (x, y) ��ǥ�� �����ϴ� �迭
int locate_dist[BASE * 10][2]; // ��ֹ��� (x, y) ��ǥ�� �����ϴ� �迭
int locate_user[1][2] = {
	{0,}
}; // �÷��̾ ��ġ�� (x, y) ��ǥ�� �����ϴ� �迭


void maingame_base_init(void); // �ܼ�â �� ���� ���� �⺻ ��� ����
void Game_start_Easy_mode_init(); //
void maingame_map_printing();
void maingame_map_init(void); // �� ���� ���(��, ���, ��ֹ�) ���� ����



void on_flag_f(void); // �÷��̾ ��߿� ��ġ�� ��
int check_flag_t(void); // �÷��̾ ���� �Ϲ� ������ Ȯ��

int main(void)
{
	base_setting();
	map_setting();

	int x = 1, y = (MAX_Y - 2), ch;

	while (1)
	{
		gotoxy(x, y);
		printf("*\b");

		locate_user[0][0] = x;
		locate_user[0][1] = y;

		on_flag_f(); // �÷��̾ ���Ƽ ����� ������� Ȯ��

		if (check_flag_t()) // �÷��̾ �Ϲ� ����� �������, �� ��Ҵ��� Ȯ��
		{
			Sleep(1000); // �� ���� ��� ���� ȭ�� ���, 1�� �� ���α׷� ����
			break;
		}

		ch = _getch();

		if (ch == 224) // ����Ű ó��
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

void maingame_base_init(void) // �ܼ�â �� ���� ���� �⺻ ��� ����
{
	srand((unsigned)time(NULL));
	system("mode con: cols=200 lines=100"); // �ܼ�â�� ũ�� ����, cols = ��, lines = ��
	CursorClosing();
	SetTextcolor(11, 0); // ��µ� �ؽ�Ʈ�� ����
}

void Game_start_Easy_mode()
{

}

void maingame_map_printing(int difficulty)
{
	int MAX_X, MAX_Y;
	switch (difficulty)
	{
		case Easy: 
			MAX_X = Easy_Map_Max_x;


	}
	for (int i = 0; i < MAX_Y; i++) // �⺻ �� ���
	{
		for (int j = 0; j < MAX_X; j++)
		{
			if ((i == 0) && (j == 0))
				printf("��");

			else if (i == 0 && (j == (MAX_X - 1)))
				printf("��");

			else if (i == (MAX_Y - 1) && (j == 0))
				printf("��");

			else if (i == (MAX_Y - 1) && (j == (MAX_X - 1)))
				printf("��");

			else if (i == 0 || (i == MAX_Y - 1))
				printf("��");

			else if (j == 0 || (j == MAX_X - 1))
				printf("��");

			else
				printf(" ");
		}
		printf("\n");
	}
}
void map_setting(int difficulty) // �� ���� ���(��, ���, ��ֹ�) ���� ����
{
	int obstacle = 0; // ������ ���� �� ũ��, ��� ���� ����(�ٸ� �ҽ� ���Ͽ� difficulty ������ Ȱ���� ����)


	if (difficulty == 0)
		MAX_X = 20, MAX_Y = 10, FLAGS_T = 2, FLAGS_F = 1;

	else if (difficulty == 1)
		MAX_X = 40, MAX_Y = 20, FLAGS_T = 20, FLAGS_F = 5;

	else
		MAX_X = 60, MAX_Y = 29, FLAGS_T = 50, FLAGS_F = 15;


	for (int i = 2; i < MAX_Y - 2; i++) // ��ֹ��� ������ ��ġ ����(�� ù �ٰ� �� �Ʒ� �� ����)
	{
		for (int j = 1; j < 1 + (rand() % (MAX_X - 3)); j++) // x�࿡�� ������ ��ֹ� ���� ���� ����
		{
			int dist_x = 2 + rand() % (MAX_X - 4); // ��ֹ��� x ��ǥ

			gotoxy(dist_x, i); // ��ֹ� ��ġ
			printf("#");

			locate_dist[distract][0] = dist_x;
			locate_dist[distract][1] = i;
		}
	}

	for (int i = 0; i < (FLAGS_T + FLAGS_F); i++) // ����� ������ ��ġ ���� �� ��ǥ ����
	{
		int x_locate = 1 + rand() % (MAX_X - 3); // ����� ������ ���� �մ� ���� �߻�
		int y_locate = 1 + rand() % (MAX_Y - 2);

		if (x_locate == 1 && y_locate == (MAX_Y - 2)) // ���� ��ġ�� �������� ����
		{
			i--;
			continue;
		}

		if (i < FLAGS_T) // ��¥ ����� ��ġ ����
		{
			gotoxy(x_locate, y_locate);
			printf("��"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���

			locate_flags_t[i][0] = x_locate;
			locate_flags_t[i][1] = y_locate;
		}

		else // ��¥ ����� ��ġ ����
		{
			gotoxy(x_locate, y_locate);
			printf("��"); // ��� ������ �ĺ��� �̡ڡ�ǢȢ���

			locate_flags_f[i - FLAGS_T][0] = x_locate;
			locate_flags_f[i - FLAGS_T][1] = y_locate;
		}
	}
}


void on_flag_f(void) // �÷��̾ ���Ƽ ��߿� ��ġ�� ��
{
	for (int i = 0; i < FLAGS_F; i++) // �÷��̾ ���Ƽ ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (locate_flags_f[i][0] == locate_user[0][0] && locate_flags_f[i][1] == locate_user[0][1])
		{
			gotoxy(MAX_X + 10, 2);
			printf("���Ƽ ����Դϴ�!");
			Sleep(3000);

			gotoxy(MAX_X + 10, 4);
			printf("������ Ǫ�ž� ���� �� �ֽ��ϴ�.");

			gotoxy(MAX_X + 10, 5);
			printf("����Ű�� ������ �ٽ� ������ ���ư��ϴ�."); // ����� ������ ������ ��� �ٷ� �Ѿ��

			locate_flags_f[i][0] = locate_flags_f[i][1] = 0;
		}
	}
}

int check_flag_t(void) // �÷��̾ �Ϲ� ��߿� ��ġ�� ��
{
	static int count = 0;

	for (int i = 0; i < FLAGS_T; i++) // �÷��̾ �Ϲ� ��߿� ��ġ�ϴ��� Ȯ��, ��ġ�ϸ� �̺�Ʈ �߻�
	{
		if (locate_flags_t[i][0] == locate_user[0][0] && locate_flags_t[i][1] == locate_user[0][1])
		{
			count++;
			locate_flags_t[i][0] = locate_flags_t[i][1] = 0;
		}
	}

	if (count == FLAGS_T) // ��� �Ϲ� ����� �� ���� ���
	{
		system("cls");

		gotoxy(17, 7);
		printf("��� �Ϲ� ����� �� ��ҽ��ϴ�!");

		return 1;
	}

	return 0;
}


/*

5/25 ������ �ʿ��ϰų� �����غ� ���

	1. ���� �ִ� ũ��, ��� ���� ���� ���̵� �������� ������ �־ ���� �ʿ� (O)
		-> ���� ���� ����� ��� ��� (O)
		-> 1���� �ذ� �� ���� ������� �ʰ� ���� �Ϸ� (O)

	2. ����� ��ǻ�� ȯ�濡 ���� �� ��¿� ���� �߻�, �� ũ�� ���� �ʿ� -> ����� ����� �ʿ��� �κ�
	3. ��ֹ��� ������� ���ϰ� ���� (X)
	4. ���Ƽ ���, �Ϲ� ��� ���� �� �ش� �ڸ����� �̺�Ʈ �߻����� X ���� (O)
	5. ���Ƽ ���� ���� ���� (Ȥ�� �״�� ���ܵδ� �͵� ���)

	------------------------------------

1. ���� �� ������(O)
	-> �� ũ�� ���� ���̵� ���� 50 * 15(O), �� ũ��� ���� ����(Ŀ���� �۾�����)
	-> ��ֹ� ����(O)

2. ��� ��ġ ���� ���(O)
	-> �� ó�� �÷��̾��� ���� ��ġ(1, 13)������ ����� �������� X(O)

3. ��� ����(O)
	-> ��ȣ ��� ����, �ϴ��� ���� ���� 3��(O)
	-> ���Ƽ ���, �Ϲ� ��� ����, ���� ���� -> ���Ƽ : �Ϲ� = 1: 2(O)
	-> �Ϲ� ����� ��� ��ƾ� �ش� �� Ŭ����(O)

4. ��߿� ���� �� �̺�Ʈ ���(��)
	-> �� ����� x, y��ǥ�� ���� �� �÷��̾��� ��ǥ�� ��ġ�� ��� �̺�Ʈ �߻�(O)
	-> �Ϲ� ��� �� ���� ��� ���� ȭ�� ��� �� ���α׷� ����(O)

	-> ���� �̺�Ʈ�� �Ͼ�� ����(��)
	-> ���� ��� ��Ҵ� ���̵� �ߺ��� ��� ex) ��Ģ ��߰� �Ϲ� ����� �� ����
	-> ��Ģ ��� �ʿ�

5. �����̴� �׼�(��)
	-> ���� ��踦 ���� ���ϰ� ó��(O)
	-> ��ֹ��� ���� ���ϰ� ó��(X)


---------------------------------- �ڵ�� ���� ���� �н��̳� ���ͳ� ����� �� �����ϰ� ǥ���� �����ϸ� ���� ���� -------------------------------------------


���̵��: ��Ģ�� �ִ� ���, ��¥ ���, ��� ���߸� ����, Ʋ���� ��Ģ�� �ִ� ���

	-> ���� ��� ����:
		1. C���α׷��� �Ϲ� ����
		2. ��ǻ�Ͱ��а��� �Ϲ� ����
		3.
		4.
		5.

	-> ��Ģ ��� ����:
		1. �ð� ����
		2. ü�� ����
		3. ������ ��ƼƼ �߰� - ex) ���� ����Ʈ���� or ���
		4. ���� ��� ��ġ ����
		5. ���̵� ������� ��� ��Ģ X, �ٷ� Game Over(�翬�� ��Ģ�� �ִ� ��ߵ� X)

	-> ���� ��� ����:
		1. ���Ƽ ��߰� �Ϲ� ����� �� ����
		2. ���Ƽ ��� ����
		3. ���� ����
		4. �ð� ����
		5. ü�� ����
		6. ��ֹ� ����
*/