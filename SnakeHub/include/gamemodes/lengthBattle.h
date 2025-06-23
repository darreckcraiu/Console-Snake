#ifndef LENGTHBATTLE_H
#define LENGTHBATTLE_H

#include <Windows.h>     // for COORD
#include <vector>        
// Forward declare Snake
struct Snake;

void runLengthBattle();

void printPlayerScores(COORD center, std::vector<Snake*>& snakes);
void printScoreToWin(COORD center, const int scoreToWin);

#endif // !LENGTHBATTLE_H