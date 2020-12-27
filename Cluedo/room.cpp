#include "room.h"

static int murderIndex;

void room::chooseMurder(){
	srand(time(0));
	murderIndex = rand() % 9;
}

bool room::checkMurder(int a){
	bool b;
	a == murderIndex ? b = true : b = false;
	return b;
}
