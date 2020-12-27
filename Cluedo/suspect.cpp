#include "suspect.h"

static int murderIndex;

void suspect::chooseMurder(){
	srand(time(0));
	murderIndex = rand()%6;
}

bool suspect::checkMurder(int a) {
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
