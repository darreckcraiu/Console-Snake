#include "gameFunctions.h"        
#include "Snake.h"                
#include "console.h"         
#include "config.h"

#include <iostream>               
#include <iomanip>                
#include <vector>                 
#include <unordered_set>          
#include <random>                 
#include <windows.h>                  

using std::vector, std::string;

void resetSnake(int& head, int& tail, int& score, int& xdir, int& ydir, bool& snakeDead, std::unordered_set<COORD, COORDHash, COORDEqual>& snakeCoords) {
    head = tail = xdir = ydir = 0;
    score = 1;
    snakeDead = false;
    snakeCoords.clear();
}
void printPlayerScores(COORD center, vector<Snake*>& snakes) {
    WORD reset = getCurrentConsoleColor();
    center.X = center.X + COLS / 2 + 3;
    center.Y = center.Y - 2;
    moveCursor(center.Y, center.X);
    for (Snake* snake : snakes) {
        printByColor(snake->snakeColor, snake->snakeSymbol);
        std::cout << " : " << std::left << std::setw(3) << snake->score;
        center.Y += 2;
        moveCursor(center.Y, center.X);
    }

    setColor(reset);
}
void printScoreToWin(COORD center, const int scoreToWin) {
    WORD reset = getCurrentConsoleColor();

    center.X -= 5 + (center.X / 2);
    moveCursor(center.Y, center.X);
    setColor(TEXT_BRIGHT_GREEN);
    std::cout << "SCORE NEEDED TO WIN: " << scoreToWin;

    setColor(reset);
}
void printTitle(COORD home) {
    HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    setColor(TITLE_COLOR);
    int sleepAmount = 100;
    COORD trueHome = home;
    home.Y -= 9;
    home.X += 9;

    //print the word "SNAKE" at the top of the map
    SetConsoleCursorPosition(han, home);
    char c = SNAKE_CHAR;
    std::cout << string(7, c) + "  " + c + "     " + c + "    " + string(3, c) + "    " + c + "    " + c + "  " + string(7, c) + ' ';
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(1, c) + string(8, ' ') + c + c + "    " + c + "   " + c + "   " + c + "   " + c + "   " + c + "   " + c + "       ";
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(1, c) + string(8, ' ') + c + ' ' + c + "   " + c + "  " + c + string(5, ' ') + c + "  " + c + "  " + c + "    " + c + string(7, ' ');
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(7, c) + "  " + c + "  " + c + "  " + c + "  " + c + string(5, ' ') + c + "  " + c + ' ' + c + string(5, ' ') + string(6, c) + "  ";
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(6, ' ') + c + "  " + c + "   " + c + ' ' + c + "  " + string(7, c) + "  " + c + "  " + c + "    " + c + string(7, ' ');
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(6, ' ') + c + "  " + c + string(4, ' ') + c + c + "  " + c + string(5, ' ') + c + "  " + c + "   " + c + "   " + c + string(7, ' ');
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << string(7, c) + "  " + c + string(5, ' ') + c + "  " + c + string(3, ' ') + "  " + c + "  " + c + string(4, ' ') + c + "  " + string(7, c) + ' ';

    //now to print the word "VERSUS" at the bottom of the map
    home = trueHome; //reset home
    home.Y += ROWS + 4;
    home.X += 5;
    SetConsoleCursorPosition(han, home); //move it to below the map
    Sleep(sleepAmount);
    std::cout << c << string(5, ' ') << c << "  " << string(7, c) << "  " << string(6, c) << "   " << string(7, c) << "  " << c << string(5, ' ') << c << "  " << string(7, c);
    home.Y++;
    SetConsoleCursorPosition(han, home);
    Sleep(sleepAmount);
    std::cout << c << string(5, ' ') << c << "  " << c << string(6, ' ') << "  " << c << string(5, ' ') << c << "  " << c << string(6, ' ') << "  " << c << string(5, ' ') << c << "  " << c;
    home.Y++;
    SetConsoleCursorPosition(han, home);//2^
    Sleep(sleepAmount);
    std::cout << c << string(5, ' ') << c << "  " << c << string(6, ' ') << "  " << c << string(5, ' ') << c << "  " << c << string(6, ' ') << "  " << c << string(5, ' ') << c << "  " << c;
    home.Y++;
    SetConsoleCursorPosition(han, home);//3^
    Sleep(sleepAmount);
    std::cout << c << string(5, ' ') << c << "  " << string(6, c) << ' ' << "  " << c << ' ' << string(4, c) << ' ' << "  " << string(7, c) << "  " << c << string(5, ' ') << c << "  " << string(7, c);
    home.Y++;
    SetConsoleCursorPosition(han, home);//4^
    Sleep(sleepAmount);
    std::cout << ' ' << c << "   " << c << ' ' << "  " << c << string(6, ' ') << "  " << c << c << string(3, c) << "  " << "  " << string(6, ' ') << c << "  " << c << string(5, ' ') << c << "  " << string(6, ' ') << c;
    home.Y++;
    SetConsoleCursorPosition(han, home);//5^
    Sleep(sleepAmount);
    std::cout << "  " << c << ' ' << c << "  " << "  " << c << string(6, ' ') << "  " << c << "    " << c << ' ' << "  " << string(6, ' ') << c << "  " << c << string(5, ' ') << c << "  " << string(6, ' ') << c;
    home.Y++;
    SetConsoleCursorPosition(han, home);//6^
    Sleep(sleepAmount);
    std::cout << string(3, ' ') << c << string(3, ' ') << "  " << string(7, c) << "  " << c << string(5, ' ') << c << "  " << string(7, c) << "  " << string(7, c) << "  " << string(7, c);

    //pause slightly after the title is fully printed
    Sleep(sleepAmount * 3);
    setColor(MAP_COLOR);
}
void drawMap(COORD startPos) {
    moveCursor(startPos.Y, startPos.X);
    int y = startPos.Y;
    std::cout << CORNER1;
    for (int i = 0; i < COLS; i++) std::cout << DASH;
    std::cout << CORNER2;
    moveCursor(++y, startPos.X);

    for (int j = 0; j < ROWS; j++) {
        std::cout << BAR;
        for (int i = 0; i < COLS; i++) std::cout << DOT;
        std::cout << BAR;
        moveCursor(++y, startPos.X);
    }

    std::cout << CORNER3;
    for (int i = 0; i < COLS; i++) std::cout << DASH;
    std::cout << CORNER4;
    moveCursor(++y, startPos.X);
}
void setSnakeSegment(int snakeX[250], int snakeY[250], int index, COORD coord) {
    snakeX[index] = coord.X;
    snakeY[index] = coord.Y;
}
COORD randomCoord(std::mt19937& gen, std::uniform_int_distribution<>& distX, std::uniform_int_distribution<>& distY) {
    return { (SHORT)distX(gen),(SHORT)distY(gen) };
}
bool inSet(const COORD& coord, const std::unordered_set<COORD, COORDHash, COORDEqual>& set) {
    if (set.find(coord) == set.end())
        return false; //if not in the set
    return true;
}
bool coordsEqual(COORD coord1, COORD coord2) {
    if (coord1.X == coord2.X && coord1.Y == coord2.Y)
        return true;
    return false;
}
void eraseTail(int x[SNAKE_ARRAYS_SIZE], int y[SNAKE_ARRAYS_SIZE], int tail) {
    moveCursor(y[tail] + 1, x[tail] + 1);
    printByColor(MAP_COLOR, DOT);
}
void advanceTail(int x[SNAKE_ARRAYS_SIZE], int y[SNAKE_ARRAYS_SIZE], int& tail, std::unordered_set<COORD, COORDHash, COORDEqual>& snakeCoords) {
    snakeCoords.erase({ (SHORT)x[tail], (SHORT)y[tail] });
    tail = (tail + 1) % SNAKE_ARRAYS_SIZE;
}
void printHead(int x[SNAKE_ARRAYS_SIZE], int y[SNAKE_ARRAYS_SIZE], int head, WORD color) {
    moveCursor(y[head] + 1, x[head] + 1);
    printByColor(color, SNAKE_CHAR);
}
int whichSnakeAteApple(COORD apple, COORD snake1Head, COORD snake2Head, COORD snake3Head) {
    if (coordsEqual(apple, snake1Head))
        return 1;
    else if (coordsEqual(apple, snake2Head))
        return 2;
    else if (coordsEqual(apple, snake3Head))
        return 3;
    else
        return -1; //no snakes ate the apple
}
COORD calculateNewHeadCoord(int currentHeadX, int currentHeadY, int xdir, int ydir, COORD home) {
    int x = ((currentHeadX + xdir - home.X + COLS) % COLS) + home.X;
    int y = ((currentHeadY + ydir - home.Y + ROWS) % ROWS) + home.Y;
    return { (SHORT)x, (SHORT)y };
}