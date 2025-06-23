#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>

//FUNCTIONS PERTAINING TO THE TERMINAL WINDOW

COORD getConsoleCenter();
void moveCursor(int row, int col);
void hideCursor();
void showCursor();
void setColor(WORD color);
void applyCustomConsoleSettings();
void resetConsoleSettings();
WORD getCurrentConsoleColor();
void printByColor(WORD printColor, char ch);

#endif //CONSOLE_H