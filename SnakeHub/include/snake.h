#ifndef SNAKE_H
#define SNAKE_H

#include "config.h"
#include "console.h"
#include <unordered_set>

//structs members are public by default
//SHORT just signifies that it is usually meant to be used with COORD
struct Snake {
	//to keep track of the snake
	int snakeID = -1;
	//how the snake looks
	const char snakeSymbol = SNAKE_CHAR;
	WORD snakeColor = TEXT_BRIGHT_WHITE;
	//coordinates on the map
	COORD coordsArr[SNAKE_ARRAYS_SIZE] = { 0 };
	std::unordered_set<COORD, COORDHash, COORDEqual> coordsSet;
	//direction of movement
	struct Direction {
		SHORT x = 0;
		SHORT y = 0;
	};
	Direction dir;

	int headIndex = 0;
	int tailIndex = 0;
	int score = 1;
	bool alive = true;

	//functions
	void resetSnake() {
		coordsSet.clear();
		dir.x = 0;
		dir.y = 0;
		headIndex = 0;
		tailIndex = 0;
		score = 1;
		alive = true;
	}
	void setCoordinatesOfSegment(const COORD& coord, const int& index) {
		coordsArr[index] = coord;
	}
	void eraseTail() {
		moveCursor(coordsArr[tailIndex].Y + 1, coordsArr[tailIndex].X + 1);
		printByColor(MAP_COLOR, DOT);
	}
	void advanceTailIndex() {
		coordsSet.erase(coordsArr[tailIndex]);
		tailIndex = (tailIndex + 1) % SNAKE_ARRAYS_SIZE;
	}
	void printHead() {
		moveCursor(coordsArr[headIndex].Y + 1, coordsArr[headIndex].X + 1);
		printByColor(snakeColor, snakeSymbol);
	}
	COORD calculateNextHead(const COORD& home) {
		COORD crd;
		crd.X = ((coordsArr[headIndex].X + dir.x - home.X + COLS) % COLS) + home.X;
		crd.Y = ((coordsArr[headIndex].Y + dir.y - home.Y + ROWS) % ROWS) + home.Y;
		return crd;
	}
};

#endif // !SNAKE_H

