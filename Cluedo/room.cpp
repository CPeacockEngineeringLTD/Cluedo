#include "room.h"

static int murderIndex;// if it's not static each player has a different solution

const static std::wstring contents[9] = {// don't change you'll regret it
	L"Ball Room",
	L"Billiard Room",
	L"Conservatory",
	L"Dining Room",
	L"Hall",
	L"Kitchen",
	L"Library",
	L"Lounge",
	L"Study"
};

std::wstring room::getContents(int a){
	return contents[a];
}

void room::chooseMurder(){
	srand(time(0));
	murderIndex = rand() % 9;//nine possible rooms
}

bool room::checkMurder(int a){
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
