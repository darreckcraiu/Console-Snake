#include "console.h"
#include "config.h"
#include <iostream>
#include <Windows.h>

void moveCursor(int row, int col) {
    COORD pos = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}
void showCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}
void setColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
WORD getCurrentConsoleColor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.wAttributes; // This includes both text and background attributes
    }
    else {
        return TEXT_WHITE; // Fallback to default if it fails
    }
}
COORD getConsoleCenter() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    COORD retCoord;
    retCoord.X = csbi.srWindow.Right / 2;
    retCoord.Y = csbi.srWindow.Bottom / 2;
    return retCoord;
}
void printByColor(WORD printColor, char ch) {
    WORD reset = getCurrentConsoleColor();
    setColor(printColor);
    std::cout << ch;
    setColor(reset);
}
void applyCustomConsoleSettings() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, 74, 19 };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);
    COORD bufferSize = { 80, 25 };
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SetConsoleTextAttribute(hOut, TEXT_CYAN);
}
void resetConsoleSettings() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
