#pragma once
#include "object.h"
#include <stdlib.h>
#include <time.h>
#include <string>

class weapon : public object{
public:
	std::wstring contents[8] = {
		L"Candlestick",
		L"Dagger",
		L"Lead Pipe",
		L"Revolver",
		L"Rope",
		L"Spanner",
		L"Poison",
		L"Axe"		
	};
    virtual void chooseMurder()override;
    static bool checkMurder(int a);
};

