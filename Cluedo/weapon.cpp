#include "weapon.h"

static int murderIndex;// if it's not static each player has a different solution

const static std::wstring contents[8] = {// don't change you'll regret it
	L"Candlestick",
	L"Dagger",
	L"Lead Pipe",
	L"Revolver",
	L"Rope",
	L"Spanner",
	L"Poison",
	L"Axe"
};

std::wstring weapon::getContents(int a) {
	return contents[a];
}

void weapon::chooseMurder(){
	srand(time(0));
	int a = rand() % 9;
	murderIndex = (a * 321133) % 6;
}

bool weapon::checkMurder(int a){
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
