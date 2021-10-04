#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#define screen_x 55
#define screen_y 28
#define esc 27
#define keyup 72
#define keydown 80
#define keyleft 75
#define keyright 77
///////////////////PROTORYPE FUNCTION ////////////////////////////////
int setConsole(); //ตั้งกรอบหน้าจอ
int setMode();
void initnumber();
void drawframe();
void movenum_up();
void movenum_down();
void movenum_left();
void movenum_right();
void fill_number_to_screen();
void setcursor(bool visible); //เปิดปิดcursor
void gotoxy(SHORT x, SHORT y);
void setcolor(int fg, int bg);
char cursor(SHORT x, SHORT y);
//////////////////////GLOBAL VARIABLE/////////////////////////////////
unsigned int score = 0;
int numberposition_x[4] = {9, 21, 33, 45};
int numberposition_y[4] = {9, 14, 19, 24};
int numberonscreen[4][4] = {{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}}; //mini 2048  [y][x]
bool playing = true;
bool moving = false;
struct number
{
    int position_x;
    int position_y;
    unsigned int value;
    int position;
};
struct number number[100];
HANDLE wHnd;
HANDLE rHnd;
SMALL_RECT windowSize = {0, 0, screen_x - 1, screen_y - 1};
DWORD fdwMode;
//////////////////////////////MAIN////////////////////////////////////
int main()
{
    char ch;
    setcursor(false);
    setConsole();
    setMode();
    drawframe();
    initnumber();
    gotoxy(0, 0);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", numberonscreen[i][j]);
        }
        printf("\n");
    }
    fill_number_to_screen();
    /*while (playing)
    {
        if (kbhit())
        {
            ch = getch();
            if (ch == keyup)
            {
                movenum_up();
            }
            else if (ch == keydown)
            {
                movenum_down();
            }
            else if (ch == keyleft)
            {
                movenum_left();
            }
            else if (ch == keyright)
            {
                movenum_right();
            }
        }
        fflush(stdin);
    }*/
    getch();
    return 0;
}
//////////////////////////FUNCTION////////////////////////////////////
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 18;
    SetConsoleCursorInfo(console, &lpCursor); //0คือปิด 1 คือเปิด
}
int setConsole()
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
}
int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(rHnd, fdwMode);
    return 0;
}
void drawframe()
{
    int i, j;
    gotoxy(0, 6);
    printf("    _______________________________________________\n");
    for (j = 1; j <= 4; j++)
    {
        for (i = 1; i <= 4; i++)
        {
            printf("   |           |           |           |           |\n");
        }
        printf("   |___________|___________|___________|___________|\n");
    }
}
void initnumber()
{
    srand(time(NULL));
    int i, x, y;
    for (i = 0; i < 2; i++)
    {

        x = rand() % 4;
        y = rand() % 4;
        while (numberonscreen[y][x] != 0)
        {
            x = rand() % 4;
            y = rand() % 4;
        }
        numberonscreen[y][x] = (rand() % 2) * 2 + 2;
    }
}
void fill_number_to_screen()
{
    int x, y;
    for (y = 0; y < 4; y++)
    {
        for (x = 0; x < 4; x++)
        {
            if (numberonscreen[y][x] == 0)
            {
                setcolor(0, 0);
            }
            else if (numberonscreen[y][x] == 2)
            {
                setcolor(0, 6);
            }
            else if (numberonscreen[y][x] == 4)
            {
                setcolor(7, 1);
            }
            else if (numberonscreen[y][x] == 8)
            {
                setcolor(7, 2);
            }
            else if (numberonscreen[y][x] == 16)
            {
                setcolor(7, 5);
            }
            else if (numberonscreen[y][x] == 32)
            {
                setcolor(7, 12);
            }
            else if (numberonscreen[y][x] == 64)
            {
                setcolor(7, 13);
            }
            else if (numberonscreen[y][x] == 128)
            {
                setcolor(7, 3);
            }
            else if (numberonscreen[y][x] == 256)
            {
                setcolor(0, 11);
            }
            else if (numberonscreen[y][x] == 512)
            {
                setcolor(7, 4);
            }
            else if (numberonscreen[y][x] == 1024)
            {
                setcolor(0, 7);
            }
            else if (numberonscreen[y][x] == 2048)
            {
                setcolor(0, 15);
            }
            if (numberonscreen[y][x] < 10)
            {
                gotoxy(numberposition_x[x] - 3, numberposition_y[y] - 1);
                printf("       ");
                gotoxy(numberposition_x[x] - 3, numberposition_y[y]);
                printf("   %d   ", numberonscreen[y][x]);
                gotoxy(numberposition_x[x] - 3, numberposition_y[y] + 1);
                printf("       ");
            }
        }
    }
}
void movenum_up()
{
}
void gotoxy(SHORT x, SHORT y)
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
char cursor(SHORT x, SHORT y)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2];
    COORD c = {x, y};
    DWORD num_read;
    if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
    {
        return '\0';
    }
    else
    {
        return buf[0];
    }
}