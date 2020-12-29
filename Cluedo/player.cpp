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

void player::setmapX(int a){
	xPos = ((a - startingX) / increment) * increment + startingX;
}

void player::setmapY(int a){
	yPos = ((a - startingY) / increment) * increment + startingY;
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
	numberOfMoves = 0;
	if (suspect::checkMurder(a - 1) && room::checkMurder(b - 1) && weapon::checkMurder(c - 1)) return true;
	else return false;
}

int player::rollDice() {
	if(rolled)return 0;
	srand(time(0));
	int a = (rand() % 6) + 1;//6 possible dice values 1 is added so that 0 is never rolled except in error
	setNumberOfMoves(a);
	rolled = true;
	return a;
}