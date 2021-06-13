#pragma once
#include "Basewindow.h"
#include "windowsx.h"
#include <future>
#include <chrono>
#include <algorithm>
#include <list>
#include <tchar.h>
#include <d2d1.h>
#include <fstream>
#include <sstream>
#include <random>
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
	int numberOfPlayers, chosenSuspect, chosenRoom, chosenWeapon, playerIndex;
	bool bScratch, bLite;
	enum cards{
		MUSTARD = 7, GREEN, PEACOCK, PLUM, SCARLETT, WHITE,
		CANDLESTICK, DAGGER, LEADPIPE, REVOLVER, ROPE, SPANNER, POISON, AXE,
		LITE, SCRATCH, FULL
	};
	enum locations{
		BALL=1, BILLIARD, CONSERVATORY, DINING, HALL, KITCHEN, LIBRARY, LOUNGE, STUDY
	};
	player players[6];
	HMENU hMenubar = CreateMenu();
	HMENU hMenu = CreateMenu();
	HMENU hAccuse = CreateMenu();
	HMENU hRoll = CreateMenu();
	HMENU hSuspect = CreatePopupMenu();
	HMENU hWeapon = CreatePopupMenu();
	HMENU hPlayers = CreatePopupMenu();
	bool suspectChecker(int& suspect, int& room, int& weapon, player pa[]);
	void playerReset();
	void nextPlayer();
	void gotoMouse(int x, int y);
	void begin();
	void distributeCards(std::vector<int>& v, const int cardsPerPlayer, std::string file);
public:
	MainWindow();
	PCWSTR ClassName() const override{ return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	bool OnCreate();
	void Update();
};