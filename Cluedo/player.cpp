#include "player.h"

void player::setNumberOfMoves(int a){
    numberOfMoves = a;
}

void player::setX(int a){
	xPos = startingX + a * increment;
}

void player::setY(int a){
	yPos = startingY + a * increment;
}

int player::getNumberOfMoves(){
    return numberOfMoves;
}

int player::getmapX(){
	return (xPos - startingX) / increment;
}

int player::getmapY(){
	return (yPos - startingY) / increment;;
}

int player::getX(){
	return xPos;
}

int player::getY(){
	return yPos;
}

bool player::makeAccusation(int a, int b, int c) {
	if (suspect::checkMurder(a) && room::checkMurder(b) && weapon::checkMurder(c)) return true;
	else return false;
}

int player::rollDice() {
	srand(time(0));
	int a = (rand() % 6) + 1;
	setNumberOfMoves(a);
	return a;
}