#include <Windows.h>

void gotoxy(short int x, short int y)

{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}