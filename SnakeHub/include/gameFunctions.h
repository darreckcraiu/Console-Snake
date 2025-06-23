#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "config.h"
#include <vector>
#include <unordered_set>
#include <random>
#include <windows.h> // For COORD and WORD

// Forward declarations
struct Snake;
struct COORDHash;
struct COORDEqual;

//gamemodes
void runLengthBattle();

void printTitle(COORD home);
void drawMap(COORD startPos);
COORD randomCoord(std::mt19937& gen, std::uniform_int_distribution<>& distX, std::uniform_int_distribution<>& distY);
bool inSet(const COORD& coord, const std::unordered_set<COORD, COORDHash, COORDEqual>& set);
bool coordsEqual(COORD coord1, COORD coord2);
int whichSnakeAteApple(COORD apple, COORD snake1Head, COORD snake2Head, COORD snake3Head);

#endif