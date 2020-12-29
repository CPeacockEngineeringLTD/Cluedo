#pragma once
#include <string>
#include <stdlib.h>
#include <time.h>

class room{
public:
    static std::wstring getContents(int a);
    static void chooseMurder();
    static bool checkMurder(int a);
};
