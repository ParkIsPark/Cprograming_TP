#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

//��� ������ ������ ����
typedef enum CursorInput {
    Start,///���� 0, 1, 2�� �����մϴ�
    Story,
    Quit
}CursorInput;//Ŀ���� ��� �ִ��� ȣ�����ϴ� ���� �������ֱ� ����.

typedef enum difficultyy {
    Easy,///���� 0, 1, 2�� �����մϴ�
    Normal,
    Hard
}Gamedifficulty;
//
int main()
{
    CursorClosing(); // Ŀ���� ����������
    Game_Start_Screen_draw(); // ���� ȭ�� �׸�
    Game_Start_menu_Screen_draw(3); // �⺻ ���� �׸���
    switch(Game_Select_menu_control(3, Game_Start_menu_Screen_draw))//���� �޴� ������ �޴��� 3���̹Ƿ� 3�� ��
    {
        case Start:
            Game_Difficulty_Select_Screen_draw(3);
            break;

        case Story:
            Game_Story_Select_Screen_draw(3);//���丮�� �� ������ �ٷ� ���̵� ���� ȭ������ �Ѿ.
            system("cls");//ȭ�� �ʱ�ȭ
            Game_Difficulty_Select_Screen_draw(3);
            break;
        case Quit:
            system("cls");
            printf("������ �����մϴ�");//���� ���� ��ũ��, ����� ���� �Լ��� ���� ���� �Ҹ�Ȯ��.
            return 0;
            break;
    }
    //���̵� ���� ȭ��
    switch (Game_Select_menu_control(3, Game_Difficulty_Select_Screen_draw))//���� �޴� ������ �޴��� 3���̹Ƿ� 3�� ��
    {
    case Easy:
        Game_start_Easy_mode();
        break;

    case Normal:
        system("cls");
        printf("�븻!");
        break;
    case Hard:
        system("cls");
        printf("�ϵ�!");//���� ���� ��ũ��, ����� ���� �Լ��� ���� ���� �Ҹ�Ȯ��.
        return 0;
        break;
    }
  
}
