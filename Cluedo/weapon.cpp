#include "weapon.h"

static int murderIndex;

void weapon::chooseMurder(){
	srand(time(0));
	murderIndex = rand() % 6;
}

bool weapon::checkMurder(int a){
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
