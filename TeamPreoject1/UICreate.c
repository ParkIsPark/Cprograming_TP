#include "GameUI.h"



//��ŸƮ ���� �޴��� ���� define�� ��������
#define Start_Menu_x 53//�̰� �ٲٸ� startmenu�� �׷����� ��ġ�� �޶����ϴ�
#define Start_Menu_y 18

#define diff_select_menu_x 53 //�곻�� �ٲٸ� ���̵� ���� �޴��� �׷����� ��ġ�� �޶����ϴ�. 
#define diff_select_menu_y 18

typedef enum CursorInput {
	Start,///���� 0, 1, 2�� �����մϴ�
	Story,
	Quit
}CursorInput;

typedef enum difficultyy {
	Easy,///���� 0, 1, 2�� �����մϴ�
	Normal,
	Hard
}Gamedifficulty;
//

void Game_Start_Screen_draw()//���� ó�� �����Ҷ� �׸� �׸��� �Լ�
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
	printf("  ��");
	Sleep(200);
	//���� ��Ŀ���� : Ŀ���� ���� ���� �׸� �׸���, ���߰�, �ٽ� �׸���, ���߰� �ݺ�
}

//�޴� ����Ʈ�ҋ� ���Ǵ� �Լ���
extern int Cursor_input;//�ۿ��� �޾ƿ��� �Ű�������
void Game_Start_menu_Screen_draw(int Cursor_input)//��ŸƮ �޴� �׷���.
{
	switch (Cursor_input)//Ŀ���� ��� ���ִ��� Ȯ�ι޾Ƽ� �Է¹ޱ� ������, �ٲ� ������ �ٲ��� �� ����.
	{
		case Start://���ڻ����� �ٲ��� �� ���� ������, �׻� ����� �ٽ� �׷���.
			printf(" ");
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//�ؽ�Ʈ �Ķ��� ��� ������. Ŀ���� �ٲ���.
			gotoxy(Start_Menu_x+1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y+2); printf("���丮");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
		case Story:
			printf(" ");//Ŀ�� �����ְ�
			gotoxy(Start_Menu_x, Start_Menu_y+2);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y + 2);
			break;
		case Quit:
			printf(" ");//Ŀ�� �����ְ�
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			printf(">\b");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextColor(15, 0);
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			SetTextcolor(1, 0);
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			SetTextcolor(15, 0);
			gotoxy(Start_Menu_x, Start_Menu_y + 4);
			break;
		default://���� ó�� �ԷµǾ��� ��
			gotoxy(Start_Menu_x, Start_Menu_y);
			printf(">\b");
			SetTextcolor(1, 0);//�ؽ�Ʈ �Ķ��� ��� ������
			gotoxy(Start_Menu_x + 1, Start_Menu_y); printf("���ӽ���");
			SetTextcolor(15, 0);//�ؽ�Ʈ �Ͼ�� ��� ������
			gotoxy(Start_Menu_x + 2, Start_Menu_y + 2); printf("���丮");
			gotoxy(Start_Menu_x + 3, Start_Menu_y + 4); printf("����");
			gotoxy(Start_Menu_x, Start_Menu_y);
			break;
	}
}
void Game_Difficulty_Select_Screen_draw(int Cursor_input)
{
	switch (Cursor_input)//Ŀ���� ��� ���ִ��� Ȯ�ι޾Ƽ� �Է¹ޱ� ������, �ٲ� ������ �ٲ��� �� ����.
	{
	case Easy://���ڻ����� �ٲ��� �� ���� ������, �׻� ����� �ٽ� �׷���.
		printf(" ");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);////////////////////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	case Normal:
		printf(" ");//Ŀ�� �����ְ�
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextcolor(1, 0);//////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y + 2);
		break;
	case Hard:
		printf(" ");//Ŀ�� �����ְ�
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		printf(">\b");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y); printf("����");
		SetTextColor(15, 0);
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 2); printf("����");
		SetTextcolor(1, 0);///////////////////////////////////////
		gotoxy(diff_select_menu_x + 1, diff_select_menu_y + 4); printf("�����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x, diff_select_menu_y + 4);
		break;
	default://���� ó�� �ԷµǾ��� ��
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		printf(">\b");
		SetTextcolor(1, 0);///////////////////////////////////////////////////
		gotoxy(diff_select_menu_x+1, diff_select_menu_y); printf("����");
		SetTextcolor(15, 0);
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 2); printf("����");
		gotoxy(diff_select_menu_x+1, diff_select_menu_y + 4); printf("�����");
		gotoxy(diff_select_menu_x, diff_select_menu_y);
		break;
	}
}
int Game_Select_menu_control(int max_menu_amount, void(*SelectFp)(int))//�޴��� �ִ� ����� Ȯ��+�Լ� ������ ���
{
	char ch;
	int Cursor_y = 0;

	while (1)//���̵� �����ϴ� ����
	{
		ch = _getch();
		if (ch == -32) {
			ch = _getch();
			switch (ch) {
			case 72:
				Cursor_y = ((Cursor_y - 1) >= 0) ? Cursor_y - 1 : max_menu_amount - 1;// Ŀ���� ���� �̵�, ��ȯ�ϵ��� ����
				SelectFp(Cursor_y);
				break;
			case 80:
				Cursor_y = ((Cursor_y + 1) <= max_menu_amount - 1) ? Cursor_y + 1 : 0;// Ŀ���� �Ʒ��� �̵�, ��ȯ�ϵ��� ����
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
	return Cursor_y;//Ŀ���� ��� �־����� ����, 0, 1, 2�� ���·� ������.
}//���� �޴� ����Ʈ�� �����ִ� �ܺ� �Լ���
//


void Game_Story_Select_Screen_draw()//���丮 ���� ȭ��.
{
	char story[] = "������ ��ġ�� �Դ�... �߾�!!!!!";//���丮�� ������ �����
	system("cls");//�׻� ȭ�� �ʱ�ȭ
	for (int i = 0; i < 30; i++) {
		printf("%c", story[i]);
		Sleep(50);//�ѱ����ѱ��� ���
	}
}