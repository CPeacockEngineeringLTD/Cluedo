#pragma once
#include "object.h"
#include <stdlib.h>
#include <time.h>
#include <string>

class suspect : public object {
public:
	std::wstring contents[6] = {
		L"Colonel Mustard",
		L"Reverend Green",
		L"Mrs Peacock",
		L"Professor Plum",
		L"Miss Scarlett",
		L"Mrs White"
	};
	virtual void chooseMurder()override;
	static bool checkMurder(int a);
};

