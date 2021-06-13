#include "MainWindow.h"

template <typename T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

HRESULT MainWindow::CreateGraphicsResources() {
	HRESULT hr = S_OK;
	GetClientRect(m_hwnd, &rc);
	return hr;
}

bool MainWindow::OnCreate() {// Only happen after loading game
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
		return false;// -1; // Fail CreateWindowEx.
	}
	InvalidateRect(m_hwnd, nullptr, FALSE);// Populate Menus
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"File");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hAccuse, L"Accuse");
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hRoll, L"Roll Dice");
	AppendMenuW(hRoll, MF_STRING, 1, L"Roll");
	AppendMenuW(hMenu, MF_POPUP, (UINT_PTR)hPlayers, L"New Game");
	AppendMenuW(hPlayers, MF_STRING, 2, L"2 Players");
	AppendMenuW(hPlayers, MF_STRING, 3, L"3 Players");
	AppendMenuW(hPlayers, MF_STRING, 4, L"4 Players");
	AppendMenuW(hPlayers, MF_STRING, 5, L"5 Players");
	AppendMenuW(hPlayers, MF_STRING, 6, L"6 Players");
	AppendMenuW(hAccuse, MF_POPUP, (UINT_PTR)hSuspect, L"Suspect");
	AppendMenuW(hSuspect, MF_STRING, MUSTARD, L"Colonel Mustard");
	AppendMenuW(hSuspect, MF_STRING, GREEN, L"Reverend Green");
	AppendMenuW(hSuspect, MF_STRING, PEACOCK, L"Mrs Peacock");
	AppendMenuW(hSuspect, MF_STRING, PLUM, L"Professor Plum");
	AppendMenuW(hSuspect, MF_STRING, SCARLETT, L"Miss Scarlett");
	AppendMenuW(hSuspect, MF_STRING, WHITE, L"Mrs White");
	AppendMenuW(hAccuse, MF_POPUP, (UINT_PTR)hWeapon, L"Weapon");
	AppendMenuW(hWeapon, MF_STRING, CANDLESTICK, L"Candlestick");
	AppendMenuW(hWeapon, MF_STRING, DAGGER, L"Dagger");
	AppendMenuW(hWeapon, MF_STRING, LEADPIPE, L"Lead Pipe");
	AppendMenuW(hWeapon, MF_STRING, REVOLVER, L"Revolver");
	AppendMenuW(hWeapon, MF_STRING, ROPE, L"Rope");
	AppendMenuW(hWeapon, MF_STRING, SPANNER, L"Spanner");
	// Only needed for 5 & 6 player games, not currently supported fully
	//if (numberOfPlayers == 4 || numberOfPlayers == 5)AppendMenuW(hSuspect, MF_STRING, POISON, L"Poison");
	//if (numberOfPlayers == 4 || numberOfPlayers == 5)AppendMenuW(hSuspect, MF_STRING, AXE, L"Axe");
	AppendMenuW(hMenu, MF_STRING, LITE, L"Lite");
	AppendMenuW(hMenu, MF_STRING, SCRATCH, L"Scratch");
	AppendMenuW(hMenu, MF_STRING, FULL, L"Full");
	SetMenu(m_hwnd, hMenubar);
	return true;
}

void MainWindow::Update() {// happens every time anything changes
	InvalidateRect(m_hwnd, nullptr, FALSE);
	HRESULT hr = CreateGraphicsResources();
	// Construct the screen with all the players drawn
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(m_hwnd, &ps);
		HGDIOBJ oldBitmap;
		HBITMAP hb = (HBITMAP)LoadImageW(nullptr, L"Cluedo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hmustard = (HBITMAP)LoadImageW(nullptr, L"mustard.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hgreen = (HBITMAP)LoadImageW(nullptr, L"green.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hplum = (HBITMAP)LoadImageW(nullptr, L"plum.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hpeacock = (HBITMAP)LoadImageW(nullptr, L"peacock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hscarlett = (HBITMAP)LoadImageW(nullptr, L"scarlett.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP hwhite = (HBITMAP)LoadImageW(nullptr, L"white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HDC src = CreateCompatibleDC(hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
		oldBitmap = SelectObject(src, hb); // Inserting picture into our temp HDC
		// Copy image from temp HDC to window
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		// Free memory taken up by all the bitmaps
		DeleteObject(oldBitmap); 
		DeleteObject(hb);
		oldBitmap = SelectObject(src, hplum);
		BitBlt(hdc, players[0].getX(), players[0].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hplum);
		oldBitmap = SelectObject(src, hpeacock);
		BitBlt(hdc, players[1].getX(), players[1].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hpeacock);
		oldBitmap = SelectObject(src, hmustard);
		BitBlt(hdc, players[2].getX(), players[2].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hmustard);
		oldBitmap = SelectObject(src, hgreen);
		BitBlt(hdc, players[3].getX(), players[3].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hgreen);
		oldBitmap = SelectObject(src, hscarlett);
		BitBlt(hdc, players[4].getX(), players[4].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hscarlett);
		oldBitmap = SelectObject(src, hwhite);
		BitBlt(hdc, players[5].getX(), players[5].getY(), rc.right, rc.bottom, src, 0, 0, SRCCOPY);
		DeleteObject(oldBitmap);
		DeleteObject(hwhite);
		// Inserting final picture into our temp HDC
		SelectObject(src, oldBitmap);
		DeleteDC(src);
		DeleteObject(oldBitmap);
		EndPaint(m_hwnd, &ps);
		// Uncomment to see grid position
		//const std::wstring& str = std::to_wstring(players[playerIndex].getX()) + L", " + std::to_wstring(players[playerIndex].getY());
		const std::wstring& str = players[0].contents[playerIndex] + L"'s turn";
		SetWindowTextW(m_hwnd, str.c_str());
	}
}

bool MainWindow::suspectChecker(int& suspect , int& room , int& weapon, player pa[]) {// check whether they are right and give information if not
	suspect -=7;//enum offset from array index
	room--;//enum offset array index
	weapon -= 13;//enum offset array index
	_TCHAR szBuffer[100];

	// Confirmation of accusation
	_stprintf_s(szBuffer, _T("You have accused %ws in the %ws with the %ws"), const_cast<wchar_t*>(suspect::getContents(suspect).c_str()),
		const_cast<wchar_t*>(room::getContents(room).c_str()), const_cast<wchar_t*>(weapon::getContents(weapon).c_str()));

	MessageBox(m_hwnd, szBuffer, _T("Accusation"), MB_OK);

	// If correctly guessed
	if (pa[playerIndex].makeAccusation(suspect, room, weapon)) {
		MessageBox(m_hwnd, L"You have won", _T("Winner"), MB_OK);
		pa[playerIndex].rolled = true;
		suspect = 0;
		room = 0;
		weapon = 0;
		numberOfPlayers = 0;
		return true;
	}

	if (bScratch) {
		// Each player's data gets sent to individual files
		std::wofstream myfile;
		switch (playerIndex) {
		case 0:myfile.open("player1.txt", std::ios_base::app); break;
		case 1:myfile.open("player2.txt", std::ios_base::app); break;
		case 2:myfile.open("player3.txt", std::ios_base::app); break;
		case 3:myfile.open("player4.txt", std::ios_base::app); break;
		case 4:myfile.open("player5.txt", std::ios_base::app); break;
		case 5:myfile.open("player6.txt", std::ios_base::app); break;
		}

		// Randomises information given for wrong answer
		srand(time(0));
		int randOrder = (rand() % 6);// 3! == 6 so there are 6 possibilities
		switch (randOrder) {
		case 0:
			if (!(suspect::checkMurder(suspect))) myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			else if (!(room::checkMurder(room))) myfile << room::getContents(room) << " is not the murder location" << std::endl;
			else myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			break;
		case 1:
			if (!(suspect::checkMurder(suspect))) myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			else if (!(weapon::checkMurder(weapon))) myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			else myfile << room::getContents(room) << " is not the murder location" << std::endl;
			break;
		case 2:
			if (!(room::checkMurder(room))) myfile << room::getContents(room) << " is not the murder location" << std::endl;
			else if (!(suspect::checkMurder(suspect))) myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			else myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			break;
		case 3:
			if (!(room::checkMurder(room))) myfile << room::getContents(room) << " is not the murder location" << std::endl;
			else if (!(weapon::checkMurder(weapon))) myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			else myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			break;
		case 4:
			if (!(weapon::checkMurder(weapon)))myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			else if (!(suspect::checkMurder(suspect))) myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			else myfile << room::getContents(room) << " is not the murder location" << std::endl;
			break;
		case 5:
			if (!(weapon::checkMurder(weapon))) myfile << weapon::getContents(weapon) << " is not the murder weapon" << std::endl;
			else if (!(room::checkMurder(room))) myfile << room::getContents(room) << " is not the murder location" << std::endl;
			else myfile << suspect::getContents(suspect) << " is not the murderer" << std::endl;
			break;
		}
		myfile.close();

	}else if (bLite) {
		// Message box for outcome
		_TCHAR szBuffera[100];
		_TCHAR szBufferb[100];
		_TCHAR szBufferc[100];
		_stprintf_s(szBuffera, _T("%ws is not the murderer"), const_cast<wchar_t*>(suspect::getContents(suspect).c_str()));
		_stprintf_s(szBufferb, _T("%ws is not the murder location"), const_cast<wchar_t*>(room::getContents(room).c_str()));
		_stprintf_s(szBufferc, _T("%ws is not the murder weapon"), const_cast<wchar_t*>(weapon::getContents(weapon).c_str()));

		// Randomises information given for wrong answer
		srand(time(0));
		int randOrder = (rand() % 6);// 3! == 6 so there are 6 possibilities
		switch (randOrder) {
		case 0:
			if (!(suspect::checkMurder(suspect))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			else if (!(room::checkMurder(room))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			break;
		case 1:
			if (!(suspect::checkMurder(suspect))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			else if (!(weapon::checkMurder(weapon))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			break;
		case 2:
			if (!(room::checkMurder(room))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			else if (!(suspect::checkMurder(suspect))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			break;
		case 3:
			if (!(room::checkMurder(room))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			else if (!(weapon::checkMurder(weapon))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			break;
		case 4:
			if (!(weapon::checkMurder(weapon))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			else if (!(suspect::checkMurder(suspect))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			break;
		case 5:
			if (!(weapon::checkMurder(weapon))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
			else if (!(room::checkMurder(room))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
			else MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
			break;
		}
	}else MessageBox(m_hwnd, L"One of your fellow players has that information.\nUnless of course you are bluffing:D", L"Not this Time", MB_OK);
	
	//reset everything
	players[playerIndex].rolled = false;
	++playerIndex;
	playerIndex %= numberOfPlayers;
	suspect = 0;
	room = 0;
	weapon = 0;
	Update();
	return false;
}

void MainWindow::playerReset() { // puts players back in starting positions
	players[0].setX(5);
	players[0].setY(23);//plum
	players[1].setX(18);
	players[1].setY(23);//peacock
	players[2].setX(7);
	players[2].setY(0);//mustard
	players[3].setX(24);
	players[3].setY(14);//green
	players[4].setX(0);
	players[4].setY(7);//scarlett
	players[5].setX(24);
	players[5].setY(9);//white
}

void MainWindow::nextPlayer() {// When players' turn is finished
	if (!(players[playerIndex].getNumberOfMoves())) {
		players[playerIndex].rolled = false;
		playerIndex++;
		playerIndex %= numberOfPlayers;
		chosenRoom = 0;
		chosenSuspect = 0;
		chosenWeapon = 0;
	}
}

void MainWindow::gotoMouse(int x, int y) {// When leaving a room
	players[playerIndex].setmapX(x);
	players[playerIndex].setmapY(y);
	players[playerIndex].location = 0;
	players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
}

void MainWindow::begin() {// executed at the start of game
	playerIndex = 0;
	for (int i = 0; i < numberOfPlayers; i++) {
		players[i].location = 0;
		players[i].rolled = false;
	}
	playerReset();
	suspect::chooseMurder();
	room::chooseMurder();
	weapon::chooseMurder();
	std::vector<int>cards;
	if (!bLite && !bScratch) {
		for (int i = 0; i < 6; i++) {
			if (suspect::checkMurder(i))continue;// don't distribute murder cards to players
			cards.push_back(i);
		}
		for (int i = 0; i < 9; i++) {
			if (room::checkMurder(i))continue;// don't distribute murder cards to players
			cards.push_back(i + 6);
		}
		for (int i = 0; i < 6; i++) {
			if (weapon::checkMurder(i))continue;// don't distribute murder cards to players
			cards.push_back(i + 15);
		}
		int numberOfCards = cards.size();
		int cardsPerPlayer = cards.size() / numberOfPlayers;
		unsigned num = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(cards.begin(), cards.end(), std::default_random_engine(num));
		std::wofstream myfile;
		// add the randomly selected cards tp the players sheets
		distributeCards(cards, cardsPerPlayer, "player1.txt");
		distributeCards(cards, cardsPerPlayer, "player2.txt");
		if (!cards.empty())distributeCards(cards, cardsPerPlayer, "player3.txt");
		if (!cards.empty())distributeCards(cards, cardsPerPlayer, "player4.txt");
		if (!cards.empty())distributeCards(cards, cardsPerPlayer, "player5.txt");
		if (!cards.empty())distributeCards(cards, cardsPerPlayer, "player6.txt");
	}
	Update();
}

void MainWindow::distributeCards(std::vector<int>& v, const int cardsPerPlayer, std::string file) {
	int numberOfCards = v.size();
	std::wofstream myfile;
	for (int i = v.size(); i > numberOfCards - cardsPerPlayer; i--) {
		myfile.open(file, std::ios_base::app);
		if (v[i - 1] < 6) myfile << suspect::getContents(v[i - 1]) << " is not the murderer" << std::endl;
		else if (v[i - 1] < 15) myfile << room::getContents(v[i - 1] - 6) << " is not the murder location" << std::endl;
		else myfile << weapon::getContents(v[i - 1] - 15) << " is not the murder weapon" << std::endl;
		myfile.close();
		v.pop_back();
		if (!v.size())break; //exit if no cards are left
	}
}

MainWindow::MainWindow() :
	pFactory(nullptr), numberOfPlayers(0), chosenRoom(0), chosenSuspect(0), chosenWeapon(0), playerIndex(0),
	bScratch(false), bLite(false) { }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {// Handles mouse and keyboard input
	int score;
	constexpr auto mapHeight = 26;
	switch (uMsg) {
	case WM_COMMAND:// Handles menu inputs
		switch (LOWORD(wParam)) {
		case 1:// dice roll
			if (!players[playerIndex].getNumberOfMoves()) {
				score = players[playerIndex].rollDice();
				_TCHAR szBuffer[100];
				_stprintf_s(szBuffer, _T("You have rolled a %i"), score);
				MessageBox(m_hwnd, szBuffer, _T("Dice Score"), MB_OK);
			}
			break;
		case 2:
			numberOfPlayers = 2;
			begin();
			break;
		case 3:
			numberOfPlayers = 3;
			begin();
			break;
		case 4:
			numberOfPlayers = 4;
			begin();
			break;
		case 5:
			numberOfPlayers = 5;
			begin();
			break;
		case 6:
			numberOfPlayers = 6;
			begin();
			break;
		case MUSTARD:
			chosenSuspect = MUSTARD;//enum to array position
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case GREEN:
			chosenSuspect = GREEN;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case PEACOCK:
			chosenSuspect = PEACOCK;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case PLUM:
			chosenSuspect = PLUM;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case SCARLETT:
			chosenSuspect = SCARLETT;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case WHITE:
			chosenSuspect = WHITE;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case CANDLESTICK:
			chosenWeapon = CANDLESTICK;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case DAGGER:
			chosenWeapon = DAGGER;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case LEADPIPE:
			chosenWeapon = LEADPIPE;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case REVOLVER:
			chosenWeapon = REVOLVER;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case ROPE:
			chosenWeapon = ROPE;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case SPANNER:
			chosenWeapon = SPANNER;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case POISON://not to be used in 2,3 & 6 player games
			chosenWeapon = POISON;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case AXE://not to be used in 2,3 & 6 player games
			chosenWeapon = AXE;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players);
			break;
		case LITE: bLite = true; bScratch = false; break;
		case SCRATCH: bLite = false; bScratch = true; break;
		case FULL: bLite = false; bScratch = false; break;
		}
		break;
	case WM_KEYDOWN:// When pressing the arrow keys. Handles incorrect entrances
		if (wParam == VK_LEFT && !players[playerIndex].location) {
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX())
				+ players[playerIndex].getmapY() + 1] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setX(players[playerIndex].getmapX() - 1);
				nextPlayer();
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX())
				+ players[playerIndex].getmapY() + 1] == 'E') {
				players[playerIndex].setX(players[playerIndex].getmapX() - 2);
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 2 && players[playerIndex].getmapY() == 17) { players[playerIndex].location = chosenRoom = STUDY; }
				else if (players[playerIndex].getmapX() == 5 && players[playerIndex].getmapY() == 11) { players[playerIndex].location = chosenRoom = HALL; }
				else if (players[playerIndex].getmapX() == 5 && players[playerIndex].getmapY() == 12) { players[playerIndex].location = chosenRoom = HALL; }
				else if (players[playerIndex].getmapX() == 4 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = LOUNGE; }
				else if (players[playerIndex].getmapX() == 9 && players[playerIndex].getmapY() == 20) { players[playerIndex].location = chosenRoom = LIBRARY; }
				Update();
			}
		}
		if (wParam == VK_RIGHT && !players[playerIndex].location) {
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX() + 2)
				+ players[playerIndex].getmapY() + 1] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setX(players[playerIndex].getmapX() + 1);
				nextPlayer();
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX() + 2)
				+ players[playerIndex].getmapY() + 1] == 'E') {
				players[playerIndex].setX(players[playerIndex].getmapX() + 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 13 && players[playerIndex].getmapY() == 22) { players[playerIndex].location = chosenRoom = BILLIARD; }
				else if (players[playerIndex].getmapX() == 18 && players[playerIndex].getmapY() == 9) { players[playerIndex].location = chosenRoom = BALL; }
				else if (players[playerIndex].getmapX() == 18 && players[playerIndex].getmapY() == 14) { players[playerIndex].location = chosenRoom = BALL; }
				else if (players[playerIndex].getmapX() == 10 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = DINING; }
				else if (players[playerIndex].getmapX() == 21 && players[playerIndex].getmapY() == 18) { players[playerIndex].location = chosenRoom = CONSERVATORY; }
				else if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 4) { players[playerIndex].location = chosenRoom = KITCHEN; }
				Update();
			}
		}
		if (wParam == VK_UP && !players[playerIndex].location && (players[playerIndex].getX() != 155 || players[playerIndex].getY() != 203)) {
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX()
				+ 1) + players[playerIndex].getmapY()] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setY(players[playerIndex].getmapY() - 1);
				nextPlayer();
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX()
				+ 1) + players[playerIndex].getmapY()] == 'E') {
				players[playerIndex].setY(players[playerIndex].getmapY() - 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 14) { players[playerIndex].location = chosenRoom = BALL; }
				else if (players[playerIndex].getmapX() == 12 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = DINING; }
				else if (players[playerIndex].getmapX() == 4 && players[playerIndex].getmapY() == 13) { players[playerIndex].location = chosenRoom = HALL; }
				Update();
			}
		}
		if (wParam == VK_DOWN && !players[playerIndex].location && (players[playerIndex].getX() != 500 || players[playerIndex].getY() != 433)
			&& (players[playerIndex].getX() != 109 || players[playerIndex].getY() != 410)) {
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX() + 1)
				+ players[playerIndex].getmapY() + 2] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setY(players[playerIndex].getmapY() + 1);
				nextPlayer();
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[mapHeight * (players[playerIndex].getmapX() + 1)
				+ players[playerIndex].getmapY() + 2] == 'E') {
				players[playerIndex].setY(players[playerIndex].getmapY() + 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 9) { players[playerIndex].location = chosenRoom = BALL; }
				else if (players[playerIndex].getmapX() == 15 && players[playerIndex].getmapY() == 19) { players[playerIndex].location = chosenRoom = BILLIARD; }
				else if (players[playerIndex].getmapX() == 8 && players[playerIndex].getmapY() == 18) { players[playerIndex].location = chosenRoom = LIBRARY; }
				Update();
			}
		}
		return 0;
	// Handles mouse input when going in secret passages. Hardcoded values are map locations
	case WM_LBUTTONDOWN:
		switch (players[playerIndex].location) {// Also moves players out of rooms to corresponding spaces
		case BALL:
			if (GET_X_LPARAM(lParam) > 477 && GET_Y_LPARAM(lParam) > 203 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 226 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 477 && GET_Y_LPARAM(lParam) > 410 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 443 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 408 && GET_Y_LPARAM(lParam) > 364 && GET_X_LPARAM(lParam)
				< 431 && GET_Y_LPARAM(lParam) < 397 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 408 && GET_Y_LPARAM(lParam) > 249 && GET_X_LPARAM(lParam)
				< 431 && GET_Y_LPARAM(lParam) < 282 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}
			Update();
			break;
		case BILLIARD:
			if (GET_X_LPARAM(lParam) > 385 && GET_Y_LPARAM(lParam) > 433 && GET_X_LPARAM(lParam)
				< 408 && GET_Y_LPARAM(lParam) < 456 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 293 && GET_Y_LPARAM(lParam) > 548 && GET_X_LPARAM(lParam)
				< 316 && GET_Y_LPARAM(lParam) < 581 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}
			Update();
			break;
		case CONSERVATORY:
			if (GET_X_LPARAM(lParam) > 475 && GET_Y_LPARAM(lParam) > 455 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 470 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) < 155 && GET_Y_LPARAM(lParam) < 180 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(132);
				players[playerIndex].setmapY(180);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = LOUNGE;
			}
			Update();
			break;
		case DINING:
			if (GET_X_LPARAM(lParam) > 315 && GET_Y_LPARAM(lParam) > 225 && GET_X_LPARAM(lParam)
				< 340 && GET_Y_LPARAM(lParam) < 260 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 220 && GET_Y_LPARAM(lParam) > 180 && GET_X_LPARAM(lParam)
				< 250 && GET_Y_LPARAM(lParam) < 210 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}
			Update();
			break;
		case HALL:
			if (GET_X_LPARAM(lParam) > 130 && GET_Y_LPARAM(lParam) > 385 && GET_X_LPARAM(lParam)
				< 160 && GET_Y_LPARAM(lParam) < 420 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 200 && GET_Y_LPARAM(lParam) > 290 && GET_X_LPARAM(lParam)
				< 230 && GET_Y_LPARAM(lParam) < 440 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}
			Update();
			break;
		case KITCHEN:
			if (GET_X_LPARAM(lParam) > 430 && GET_Y_LPARAM(lParam) > 130 && GET_X_LPARAM(lParam)
				< 465 && GET_Y_LPARAM(lParam) < 165 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) < 190 && GET_Y_LPARAM(lParam) > 400 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(86);
				players[playerIndex].setmapY(433);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = STUDY;
			}
			Update();
			break;
		case LIBRARY:
			if (GET_X_LPARAM(lParam) > 292 && GET_Y_LPARAM(lParam) > 501 && GET_X_LPARAM(lParam)
				< 316 && GET_Y_LPARAM(lParam) < 526 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 223 && GET_Y_LPARAM(lParam) > 409 && GET_X_LPARAM(lParam)
				< 248 && GET_Y_LPARAM(lParam) < 434 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}
			Update();
			break;
		case LOUNGE:
			if (GET_X_LPARAM(lParam) > 175 && GET_Y_LPARAM(lParam) > 175 && GET_X_LPARAM(lParam)
				< 210 && GET_Y_LPARAM(lParam) < 210 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 475 && GET_Y_LPARAM(lParam) > 435 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(523);
				players[playerIndex].setmapY(456);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = CONSERVATORY;
			}
			Update();
			break;
		case STUDY:
			if (GET_X_LPARAM(lParam) > 131 && GET_Y_LPARAM(lParam) > 430 && GET_X_LPARAM(lParam)
				< 159 && GET_Y_LPARAM(lParam) < 460 && players[playerIndex].getNumberOfMoves()) {
				gotoMouse(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				nextPlayer();
			}else if (GET_X_LPARAM(lParam) > 425 && GET_Y_LPARAM(lParam) < 200 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(477);
				players[playerIndex].setmapY(134);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = KITCHEN;
			}
			Update();
			break;
		}
		return 0;
	case WM_LBUTTONUP:// not used currently
		//OnLButtonUp();
		return 0;
	case WM_CLOSE:
		if (MessageBox(m_hwnd, L"Really quit?", L"Cluedo", MB_OKCANCEL) == IDOK)
			DestroyWindow(m_hwnd);
		return 0;
	case WM_DESTROY:
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}