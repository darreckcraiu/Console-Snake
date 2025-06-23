#include "gameModes/lengthBattle.h"
#include "gameFunctions.h"
#include "config.h"
#include "console.h"
#include "snake.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <unordered_set>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <queue>


using std::vector;

void runLengthBattle() {
    applyCustomConsoleSettings();
    setColor(TEXT_BRIGHT_WHITE);
    std::cout << "Full screen then press enter to start...";
    setColor(TEXT_CYAN);
    getchar();
    system("cls");  // Clears the console and resets cursor to (0, 0)
    hideCursor();

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::vector<PlayerKeys> keyBindings = {
        {'w', 's', 'a', 'd', false},       // Player 0
        {72, 80, 75, 77, true},           // Player 1
        {'i', 'k', 'j', 'l', false},      // Player 2
        {'t', 'g', 'f', 'h', false},      // Player 3
        {'0', '-', '9', '=', false},      // Player 4
        {'2', '3', '1', '4', false}       // Player 5
    };

    const int SCORE_TO_WIN = 10;
    bool restart = true;
    while (restart) {
        restart = false;
        COORD center = getConsoleCenter(); //center of console
        COORD home = center;
        home.X -= COLS / 2;
        home.Y -= ROWS / 2; // home = top left corner of map
        printTitle(home);
        drawMap(home);
        printScoreToWin(center, SCORE_TO_WIN);
        //set range for random number generation
        std::uniform_int_distribution<> distX(home.X, home.X + COLS - 1);
        std::uniform_int_distribution<> distY(home.Y, home.Y + ROWS - 1);

        //create vector of snakes to account for each player. Also set some of their colors
        vector<Snake*> snakes;
        for (int i = 0; i < NUM_OF_PLAYERS; i++)
            snakes.push_back(new Snake);
        snakes[0]->snakeColor = TEXT_BRIGHT_YELLOW;
        snakes[1]->snakeColor = TEXT_BRIGHT_RED;
   /*     snakes[2]->snakeColor = TEXT_BRIGHT_MAGENTA;
        snakes[3]->snakeColor = TEXT_BRIGHT_LIME;
    */    std::queue<Snake*> deadSnakes; //keeps track of dead snakes

        std::unordered_set<COORD, COORDHash, COORDEqual> occupied; //all coords on the map that are already occupied

        COORD coord; //to avoid constantly creating new COORD variables throughout the program
        Snake* snakePtr; //same reasoning as coord^

        //choose random starting location for each snake that is not occupied
        for (Snake* snake : snakes) {
            do {
                coord = randomCoord(gen, distX, distY);
            } while (inSet(coord, occupied));
            snake->setCoordinatesOfSegment(coord, 0);
            snake->coordsSet.insert(coord);
            occupied.insert(coord);
        }

        //snake food
        COORD appleCoord = { -1,-1 };
        printPlayerScores(center, snakes);

        int gameover = 0;
        int quit = 0;
        while (!quit && !gameover) {
            // attempt to spawn apple this frame if needed
            if (appleCoord.X < 0) {
                appleCoord = randomCoord(gen, distX, distY);
                //check for collision
                if (inSet(appleCoord, occupied))
                    appleCoord.X = -1;
                if (appleCoord.X >= 0) {
                    occupied.insert(appleCoord);
                    moveCursor(appleCoord.Y + 1, appleCoord.X + 1);
                    printByColor(FOOD_COLOR, FOOD_CHAR);
                }
            }

            //attempt to respawn a snake this frame if needed
            if (!deadSnakes.empty()) {
                snakePtr = deadSnakes.front();
                //ensures that snakes only spawn in once they are completely erased from the map
                if (snakePtr->tailIndex >= snakePtr->headIndex) {
                    deadSnakes.pop(); //remove the snake from the queue
                    snakePtr->resetSnake();
                    printPlayerScores(center, snakes);
                    //give snake a new random spawn position (might be valid, might not)
                    coord = randomCoord(gen, distX, distY);
                    if (!inSet(coord, occupied)) {
                        snakePtr->setCoordinatesOfSegment(coord, 0);
                        snakePtr->coordsSet.insert(coord);
                        occupied.insert(coord);
                    }
                }
            }

            //erase tails up to the head of each snake
            for (Snake* snake : snakes) {
                if (snake->alive)
                    snake->eraseTail();
                else if (snake->tailIndex < snake->headIndex)
                    snake->eraseTail();
            }

            //check for apple being eaten
            for (Snake* snake : snakes) {
                //if the snake head landed on the apple
                if (snake->coordsArr[snake->headIndex].X == appleCoord.X && snake->coordsArr[snake->headIndex].Y == appleCoord.Y) {
                    appleCoord.X = -1;
                    occupied.erase(appleCoord);
                    snake->score++;
                    printPlayerScores(center, snakes);
                    //check for win
                    if (snake->score >= SCORE_TO_WIN) {
                        //logic here for this snake winning
                        gameover = 1;
                        break;
                    }
                }
                else {
                    occupied.erase(snake->coordsArr[snake->tailIndex]);   //erase tail from occupied
                    snake->advanceTailIndex();  //advance tailIndex
                }

            }

            //calculate new heads and check if any snake just killed itself as a result
            for (Snake* snake : snakes) {
                if (snake->alive) {
                    coord = snake->calculateNextHead(home); //coord = nextHead
                    //if the snake hits itself
                    if (inSet(coord, snake->coordsSet)) {
                        snake->alive = false;
                        deadSnakes.push(snake);
                    }
                    else {
                        occupied.insert(coord);
                        snake->coordsSet.insert(coord); //add new nead to coordsSet
                        snake->headIndex = (snake->headIndex + 1) % SNAKE_ARRAYS_SIZE; //advance head index
                        snake->setCoordinatesOfSegment(coord, snake->headIndex); //set value at new head index to the calculated coord 
                    }
                }
            }

            //check if any snakes killed each other and mark the dead ones
            //this loop will loop through the whole loop for each snake
            for (int i = 0; i < NUM_OF_PLAYERS; i++) {
                snakePtr = snakes[i];
                if (!snakePtr->alive)
                    continue;
                for (int j = 0; j < NUM_OF_PLAYERS; j++) {
                    if (i == j)
                        continue;
                    //if the head of snakePtr makes contact with any part of snakes[j]
                    if (snakes[j]->alive && inSet(snakes[j]->coordsArr[snakes[j]->headIndex], snakePtr->coordsSet)) {
                        snakes[j]->alive = false;
                        deadSnakes.push(snakes[j]);
                        //if their heads are what hit specifically. the extra check is to avoid a bug that lets one snake live anyway
                        if (coordsEqual(snakePtr->coordsArr[snakePtr->headIndex], snakes[j]->coordsArr[snakes[j]->headIndex])
                            || coordsEqual(snakePtr->coordsArr[snakePtr->headIndex], snakes[j]->coordsArr[snakes[j]->headIndex - 1])) {
                            snakePtr->alive = false;
                            deadSnakes.push(snakePtr);
                        }
                    }
                }
            }

            //print new heads
            for (Snake* snake : snakes) {
                if (snake->alive)
                    snake->printHead();
            }

            std::cout.flush();
            setColor(MAP_COLOR);

            Sleep(50);

            // Handle input
            if (_kbhit()) {
                int ch = _getch();

                if (ch == 27) quit = 1;

                for (int i = 0; i < keyBindings.size(); ++i) {
                    if (i >= snakes.size()) break;

                    Snake* s = snakes[i];
                    PlayerKeys& keys = keyBindings[i];

                    if (keys.usesArrowKeys && ch == 224) {
                        int arrow = _getch();
                        if (arrow == keys.left && s->dir.x != 1) { s->dir = { -1, 0 }; }
                        else if (arrow == keys.right && s->dir.x != -1) { s->dir = { 1, 0 }; }
                        else if (arrow == keys.down && s->dir.y != -1) { s->dir = { 0, 1 }; }
                        else if (arrow == keys.up && s->dir.y != 1) { s->dir = { 0, -1 }; }
                    }
                    else if (!keys.usesArrowKeys) {
                        if (ch == keys.left && s->dir.x != 1) { s->dir = { -1, 0 }; }
                        else if (ch == keys.right && s->dir.x != -1) { s->dir = { 1, 0 }; }
                        else if (ch == keys.down && s->dir.y != -1) { s->dir = { 0, 1 }; }
                        else if (ch == keys.up && s->dir.y != 1) { s->dir = { 0, -1 }; }
                    }
                }
            }

        }

        if (!quit) {
            snakePtr = snakes[0]; //to get rid of the error
            for (Snake* snake : snakes) {
                if (snake->score >= SCORE_TO_WIN) {
                    snakePtr = snake;
                    break;
                }
            }
            setColor(TEXT_BRIGHT_YELLOW);
            moveCursor(center.Y, center.X - 8);
            std::cout << "The winner is ";
            printByColor(snakePtr->snakeColor, snakePtr->snakeSymbol);

            Sleep(2000);  // Sleep for 2000 milliseconds (2 seconds)
            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));  // Ignore any key presses during the sleep

            moveCursor(center.Y + 5, center.X - 9);
            std::cout << "Press R to restart";
            moveCursor(center.Y + 6, center.X - 16);
            std::cout << "(Takes a couple seconds to load)";
            char ch = _getch();
            if (ch == 'r' || ch == 'R')
                restart = true;

            std::cout.flush();
            //_getch(); //not sure why but original programmer had this here
        }
    }

    showCursor();
    resetConsoleSettings();

    return;
}