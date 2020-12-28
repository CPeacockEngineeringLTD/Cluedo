#pragma once
#include "Basewindow.h"
#include "windowsx.h"
#include <future>
#include <chrono>
#include <algorithm>
#include <list>
#include <tchar.h>
#include <d2d1.h>
#include "suspect.h"
#include "player.h"
#include "room.h"
#include "weapon.h"
#pragma comment(lib, "d2d1")

template <typename T> void SafeRelease(T** ppT);
class MainWindow : public Basewindow<MainWindow> {
	ID2D1Factory* pFactory;
	RECT rc{ 0,0,600,800 };
	HRESULT CreateGraphicsResources();
	void Resize();
	int numberOfPlayers, chosenSuspect, chosenRoom, chosenWeapon, playerIndex;
	player players[6];
	suspect suspects[6];
	room rooms[9];
	weapon weapons[6];
	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();
	HMENU hAccuse = CreateMenu();
	HMENU hRoll = CreateMenu();
	HMENU hSuspect = CreatePopupMenu();
	HMENU hWeapon = CreatePopupMenu();
	HMENU hPlayers = CreatePopupMenu();
public:
	MainWindow();
	PCWSTR ClassName() const override{ return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	bool OnCreate();
	void Update();
	bool suspectChecker(int& a, int& b, int& c, player pa[], suspect sa[], room ra[], weapon wa[]);
	void playerReset();
	void nextPlayer();
	void gotoMouse(int x, int y);
};