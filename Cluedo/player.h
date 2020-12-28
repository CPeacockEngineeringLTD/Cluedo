#pragma once
#include "suspect.h"
#include "room.h"
#include "weapon.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

class player{
	int numberOfMoves;
	const int startingX = 40;
	const int startingY = 42;
	const int increment = 23;
	int xPos;
	int yPos;
public:
	int location = 0;
	bool rolled = false;
	std::wstring contents[6] = {
		L"Professor Plum",
		L"Mrs Peacock",
		L"Colonel Mustard",
		L"Reverend Green",
		L"Miss Scarlett",
		L"Mrs White"
	};
	std::string map = 
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

