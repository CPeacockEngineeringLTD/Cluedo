#pragma once
#include <stdlib.h>
#include <time.h>
#include <string>

class suspect{
public:
	static std::wstring getContents(int a);
	static void chooseMurder();
	static bool checkMurder(int a);
};

