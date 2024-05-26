#define _CRT_SECURE_NO_WARNINGS
#include "All_In_one_header.h"

//사용 가능한 열거형 정의
typedef enum CursorInput {
    Start,///각각 0, 1, 2에 대응합니다
    Story,
    Quit
}CursorInput;//커서가 어디에 있는지 호강니하는 것을 통일해주기 위함.

typedef enum difficultyy {
    Easy,///각각 0, 1, 2에 대응합니다
    Normal,
    Hard
}Gamedifficulty;
//
int main()
{
    CursorClosing(); // 커서를 지워버리고
    Game_Start_Screen_draw(); // 시작 화면 그림
    Game_Start_menu_Screen_draw(3); // 기본 세팅 그리기
    switch(Game_Select_menu_control(3, Game_Start_menu_Screen_draw))//게임 메뉴 셀렉팅 메뉴가 3개이므로 3개 씀
    {
        case Start:
            Game_Difficulty_Select_Screen_draw(3);
            break;

        case Story:
            Game_Story_Select_Screen_draw(3);//스토리를 본 다음엔 바로 난이도 선택 화면으로 넘어감.
            system("cls");//화면 초기화
            Game_Difficulty_Select_Screen_draw(3);
            break;
        case Quit:
            system("cls");
            printf("게임을 종료합니다");//게임 종료 스크린, 여기는 따로 함수로 뺴야 할지 불명확함.
            return 0;
            break;
    }
    //난이도 선택 화면
    switch (Game_Select_menu_control(3, Game_Difficulty_Select_Screen_draw))//게임 메뉴 셀렉팅 메뉴가 3개이므로 3개 씀
    {
    case Easy:
        Game_start_Easy_mode();
        break;

    case Normal:
        system("cls");
        printf("노말!");
        break;
    case Hard:
        system("cls");
        printf("하드!");//게임 종료 스크린, 여기는 따로 함수로 뺴야 할지 불명확함.
        return 0;
        break;
    }
  
}
