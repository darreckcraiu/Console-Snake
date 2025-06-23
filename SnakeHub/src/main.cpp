#include "config.h"
#include "gamemodes/lengthBattle.h"
#include "gamemodes/deathMatch.h"
#include <iostream>

//EDIT GAME SETTINGS IN config.h

int main() {
	const int mode = 2;
	switch (mode) {
		case 1: runDeathMatch(); break;
		case 2: runLengthBattle(); break;
		default: std::cout<<"\n\nERROR CHOOSING GAMEMODE\n\n";
	}
	return 0;
}

//POTENTIAL ADDITIONS/FEATURES
//update game logic to allow for multiple pieces of food to be on the map simultaneously. Should allow for the number to be easily modified in config.h
//co op gamemode(s)

//BUGS
//in all gamemodes, there exists a minor bug that allows two snakes of 1 length to 
//move right past each other by creating their new heads right past each other