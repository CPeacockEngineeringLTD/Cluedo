#pragma once
#include "object.h"
#include <string>
#include <stdlib.h>
#include <time.h>

class room : public object{
public:
    virtual void chooseMurder()override;
    static bool checkMurder(int a);
	std::wstring contents[9] = {
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
};
