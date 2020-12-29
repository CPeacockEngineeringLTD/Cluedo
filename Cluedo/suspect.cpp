#include "suspect.h"

static int murderIndex;// if it's not static each player has a different solution

const static std::wstring contents[6] = {// don't change you'll regret it
	L"Colonel Mustard",
	L"Reverend Green",
	L"Mrs Peacock",
	L"Professor Plum",
	L"Miss Scarlett",
	L"Mrs White"
};

std::wstring suspect::getContents(int a) {
	return contents[a - 1];
}

void suspect::chooseMurder(){
	srand(time(0));
	murderIndex = rand()%6;
}

bool suspect::checkMurder(int a) {
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
