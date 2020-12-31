#pragma once
#include "suspect.h"
#include "room.h"
#include "weapon.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

class player{
private:
	int numberOfMoves = 0;
	const int startingX = 40;//position in pixels of square with lowest pixel value in x
	const int startingY = 42;//position in pixels of square with lowest pixel value in y
	const int increment = 23;//square size in pixels
	int xPos = 0;
	int yPos = 0;
public:
	int location = 0;
	bool rolled = false;
	std::wstring contents[6] = {// change if you want players to start in a different order
		L"Professor Plum",
		L"Mrs Peacock",
		L"Colonel Mustard",
		L"Reverend Green",
		L"Miss Scarlett",
		L"Mrs White"
	};
	std::string map = // Used to handle collisions and false moves
		"XXXXXXXXXXXXXXXXXXXXXXXXXX"
		"XLLLLLLXOXHHHHHHXOXSSSSSSX"
		"XLLLLLLLOOHHHHHHOOSSSSSSSX"
		"XLLLLLLLOOHHHHHHOOSSSSSSSX"
		"XLLLLLLLOOHHHHHHOOESSSSSSX"
		"XLLLLLLLOOHHHHHEOOOOOOOOXX"
		"XLLLLLLEOOHHHHHHOOOOOOOOOX"
		"XXOOOOOOOOHHEEHHOOORRRRRXX"
		"XOOOOOOOOOOOOOOOOORRRRRRRX"
		"XXOOOOOOOOOXXXXXOOERRRRRRX"
		"XDDDDDDEDOOXXXXXOORRRRRRRX"
		"XDDDDDDDDOOXXXXXOOORRERRXX"
		"XDDDDDDDDOOXXXXXOOOOOOOOXX"
		"XDDDDDDDEOOXXXXXOOOBBBBEBX"
		"XDDDDDDDDOOXXXXXOOOBBBBBBX"
		"XDDDDDDDDOOXXXXXOOOBBBBBBX"
		"XDDDDDOOOOOOOOOOOOOEBBBBBX"
		"XXOOOOOOOOOOOOOOOOOBBBBBBX"
		"XOOOOOOOOAEAAAAEAOOOOOOOXX"
		"XXKKKEKOOAAAAAAAAOOOOOOOOX"
		"XKKKKKKOOEAAAAAAEOOOCCCCXX"
		"XKKKKKKOOAAAAAAAAOOECCCCCX"
		"XKKKKKKOOAAAAAAAAOOCCCCCCX"
		"XKKKKKKOOAAAAAAAAOOCCCCCCX"
		"XKKKKKKXOOOAAAAOOOXCCCCCCX"
		"XXXXXXXXXXOXXXXOXXXXXXXXXX"
		"XXXXXXXXXXXXXXXXXXXXXXXXXX";

	void setNumberOfMoves(int a);
	void setX(int a);
	void setY(int a);
	void setmapX(int a);
	void setmapY(int a);
	int getNumberOfMoves();
	int getmapX();
	int getmapY();
	int getX();
	int getY();
	bool makeAccusation(int a, int b, int c);
	int rollDice();
};

