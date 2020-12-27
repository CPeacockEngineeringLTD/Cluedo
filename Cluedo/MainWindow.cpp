#include "MainWindow.h"


constexpr unsigned long chromakey = 4281558681;
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

bool MainWindow::OnCreate() {
	if (FAILED(D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory))) {
		return false;// -1; // Fail CreateWindowEx.
	}
	InvalidateRect(m_hwnd, nullptr, FALSE);
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
	AppendMenuW(hSuspect, MF_STRING, 7, L"Colonel Mustard");
	AppendMenuW(hSuspect, MF_STRING, 8, L"Reverend Green");
	AppendMenuW(hSuspect, MF_STRING, 9, L"Mrs Peacock");
	AppendMenuW(hSuspect, MF_STRING, 10, L"Professor Plum");
	AppendMenuW(hSuspect, MF_STRING, 11, L"Miss Scarlett");
	AppendMenuW(hSuspect, MF_STRING, 12, L"Mrs White");
	AppendMenuW(hAccuse, MF_POPUP, (UINT_PTR)hWeapon, L"Weapon");
	AppendMenuW(hWeapon, MF_STRING, 13, L"Candlestick");
	AppendMenuW(hWeapon, MF_STRING, 14, L"Dagger");
	AppendMenuW(hWeapon, MF_STRING, 15, L"Lead Pipe");
	AppendMenuW(hWeapon, MF_STRING, 16, L"Revolver");
	AppendMenuW(hWeapon, MF_STRING, 17, L"Rope");
	AppendMenuW(hWeapon, MF_STRING, 18, L"Spanner");
	//if (numberOfPlayers == 4 || numberOfPlayers == 5)AppendMenuW(hSuspect, MF_STRING, 19, L"Poison");
	//if (numberOfPlayers == 4 || numberOfPlayers == 5)AppendMenuW(hSuspect, MF_STRING, 20, L"Axe");
	SetMenu(m_hwnd, hMenubar);
	return true;
}

void MainWindow::Update() {
	InvalidateRect(m_hwnd, nullptr, FALSE);
	HRESULT hr = CreateGraphicsResources();
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
		// Inserting picture into our temp HDC
		SelectObject(src, oldBitmap);
		DeleteDC(src);
		DeleteObject(oldBitmap);
		DeleteObject(hb);
		EndPaint(m_hwnd, &ps);
		// Uncomment to see frame count.
		//const std::wstring& str = std::to_wstring(players[playerIndex].getX()) + L", " + std::to_wstring(players[playerIndex].getY());
		const std::wstring& str = players[0].contents[playerIndex] + L"'s turn";
		SetWindowTextW(m_hwnd, str.c_str());
	}
}

bool MainWindow::suspectChecker(int& a, int& b, int& c, player pa[], suspect sa[], room ra[], weapon wa[]){
	_TCHAR szBuffer[100];
	_TCHAR szBuffera[100];
	_TCHAR szBufferb[100];
	_TCHAR szBufferc[100];

	_stprintf_s(szBuffer, _T("You have accused %ws in the %ws with the %ws"), const_cast<wchar_t*>(sa[0].contents[a - 1].c_str()), 
		const_cast<wchar_t*>(ra[0].contents[b - 1].c_str()), const_cast<wchar_t*>(wa[0].contents[c - 1].c_str()));
	_stprintf_s(szBuffera, _T("%ws is not the murderer"), const_cast<wchar_t*>(sa[0].contents[a - 1].c_str()));
	_stprintf_s(szBufferb, _T("%ws is not the murder location"), const_cast<wchar_t*>(ra[0].contents[b - 1].c_str()));
	_stprintf_s(szBufferc, _T("%ws is not the murder weapon"), const_cast<wchar_t*>(wa[0].contents[c - 1].c_str()));
	MessageBox(m_hwnd, szBuffer, _T("Accusation"), MB_OK);
	if (pa[0].makeAccusation(a - 1 , b - 1 , c - 1)) {
		MessageBox(m_hwnd, L"You have won", _T("Winner"), MB_OK);
		return true;
	}
	srand(time(0));
	int randOrder = (rand() % 6);
	switch (randOrder) {
	case 0:
		if (!(sa[0].checkMurder(a - 1))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
		else if (!(ra[0].checkMurder(b - 1))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
		else MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
		break;
	case 1:
		if (!(sa[0].checkMurder(a - 1))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
		else if (!(wa[0].checkMurder(c - 1))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK);
		else MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
		break;
	case 2:
		if (!(ra[0].checkMurder(b - 1))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK);
		else if (!(sa[0].checkMurder(a - 1))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
		else MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK); 
		break;
	case 3:
		if (!(ra[0].checkMurder(b - 1))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK); 
		else if (!(wa[0].checkMurder(c - 1))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK); 
		else MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
		break;
	case 4:
		if (!(wa[0].checkMurder(c - 1))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK); 
		else if (!(sa[0].checkMurder(a - 1))) MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK); 
		else MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK); 
		break;
	case 5:
		if (!(wa[0].checkMurder(c - 1))) MessageBox(m_hwnd, szBufferc, _T("Not this Time"), MB_OK); 
		else if (!(ra[0].checkMurder(b - 1))) MessageBox(m_hwnd, szBufferb, _T("Not this Time"), MB_OK); 
		else MessageBox(m_hwnd, szBuffera, _T("Not this Time"), MB_OK);
		break;
	}
	++playerIndex;
	playerIndex %= numberOfPlayers;
	a = 0;
	b = 0;
	c = 0;
	Update();
	return false;
}

void MainWindow::playerReset(){
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

void MainWindow::Resize() {
	GetClientRect(m_hwnd, &rc);
	InvalidateRect(m_hwnd, nullptr, FALSE);
}

MainWindow::MainWindow() :
	pFactory(nullptr), numberOfPlayers(2), chosenRoom(0), chosenSuspect(0), chosenWeapon(0), playerIndex(0){ }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int score, junkX, junkY;
	switch (uMsg) {
	case WM_COMMAND:// HANDLE 4&5 PLAYERS
		switch (LOWORD(wParam)) {
		case 1:
			if (!players[playerIndex].getNumberOfMoves()) {
				score = players[playerIndex].rollDice();
				_TCHAR szBuffer[100];
				_stprintf_s(szBuffer, _T("You have rolled a %i"), score);
				MessageBox(m_hwnd, szBuffer, _T("Dice Score"), MB_OK);
			}
			break;
		case 2:
			numberOfPlayers = 2;
			playerIndex = 0;
			playerReset();
			suspects[0].chooseMurder();
			rooms[0].chooseMurder();
			weapons[0].chooseMurder();
			Update();
			break;
		case 3:
			numberOfPlayers = 3;
			playerIndex = 0;
			playerReset();
			suspects[0].chooseMurder();
			rooms[0].chooseMurder();
			weapons[0].chooseMurder();
			Update();
			break;
		case 4:
			numberOfPlayers = 4;
			playerIndex = 0;
			playerReset();
			suspects[0].chooseMurder();
			rooms[0].chooseMurder();
			weapons[0].chooseMurder();
			Update();
			break;
		case 5:
			numberOfPlayers = 5;
			playerIndex = 0;
			playerReset();
			suspects[0].chooseMurder();
			rooms[0].chooseMurder();
			weapons[0].chooseMurder();
			Update();
			break;
		case 6:
			numberOfPlayers = 6;
			playerIndex = 0;
			playerReset();
			suspects[0].chooseMurder();
			rooms[0].chooseMurder();
			weapons[0].chooseMurder();
			Update();
			break;
		case 7:
			chosenSuspect = 1;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 8:
			chosenSuspect = 2;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 9:
			chosenSuspect = 3;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 10:
			chosenSuspect = 4;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 11:
			chosenSuspect = 5;			
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 12: 
			chosenSuspect = 6;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 13:
			chosenWeapon = 1;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 14:
			chosenWeapon = 2;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 15:
			chosenWeapon = 3;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 16:
			chosenWeapon = 4;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 17:
			chosenWeapon = 5;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 18:
			chosenWeapon = 6;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 19://not used in 2,3 & 6 player games
			chosenWeapon = 7;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		case 20://not used in 2,3 & 6 player games
			chosenWeapon = 8;
			if (chosenSuspect && chosenRoom && chosenWeapon)
				suspectChecker(chosenSuspect, chosenRoom, chosenWeapon, players, suspects, rooms, weapons);
			break;
		}
		break;
	case WM_KEYDOWN:// ALLOW SECRET PASSAGE
		if (wParam == VK_LEFT){
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX())
				+ players[playerIndex].getmapY() + 1] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setX(players[playerIndex].getmapX() - 1);
				if (!(players[playerIndex].getNumberOfMoves())) {
					playerIndex++;
					playerIndex %= numberOfPlayers;
				}
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX())
				+ players[playerIndex].getmapY() + 1] == 'E') {
				players[playerIndex].setX(players[playerIndex].getmapX() - 2);
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 2 && players[playerIndex].getmapY() == 17) { players[playerIndex].location = chosenRoom = 9; }
				else if (players[playerIndex].getmapX() == 5 && players[playerIndex].getmapY() == 11) { players[playerIndex].location = chosenRoom = 5; }
				else if (players[playerIndex].getmapX() == 5 && players[playerIndex].getmapY() == 12) { players[playerIndex].location = chosenRoom = 5; }
				else if (players[playerIndex].getmapX() == 4 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = 8; }
				else if (players[playerIndex].getmapX() == 9 && players[playerIndex].getmapY() == 20) { players[playerIndex].location = chosenRoom = 7; }
				Update();
			}
		}
		if (wParam == VK_RIGHT){
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX() + 2)
				+ players[playerIndex].getmapY() + 1] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setX(players[playerIndex].getmapX() + 1);
				if (!(players[playerIndex].getNumberOfMoves())) {
					playerIndex++;
					playerIndex %= numberOfPlayers;
				}
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX() + 2)
				+ players[playerIndex].getmapY() + 1] == 'E') {
				players[playerIndex].setX(players[playerIndex].getmapX() + 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 13 && players[playerIndex].getmapY() == 22) { players[playerIndex].location = chosenRoom = 2; }
				else if (players[playerIndex].getmapX() == 18 && players[playerIndex].getmapY() == 9) { players[playerIndex].location = chosenRoom = 1; }
				else if (players[playerIndex].getmapX() == 18 && players[playerIndex].getmapY() == 14) { players[playerIndex].location = chosenRoom = 1; }
				else if (players[playerIndex].getmapX() == 10 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = 4; }
				else if (players[playerIndex].getmapX() == 21 && players[playerIndex].getmapY() == 18) { players[playerIndex].location = chosenRoom = 3; }
				else if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 4) { players[playerIndex].location = chosenRoom = 6; }
				Update();
			}
		}
		if (wParam == VK_UP){
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX()
				+ 1) + players[playerIndex].getmapY()] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setY(players[playerIndex].getmapY() - 1);
				if (!(players[playerIndex].getNumberOfMoves())) {
					playerIndex++;
					playerIndex %= numberOfPlayers;
				}
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX()
				+ 1) + players[playerIndex].getmapY()] == 'E') {
				players[playerIndex].setY(players[playerIndex].getmapY() - 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 14) { players[playerIndex].location = chosenRoom = 1; }
				else if (players[playerIndex].getmapX() == 12 && players[playerIndex].getmapY() == 6) { players[playerIndex].location = chosenRoom = 4; }
				else if (players[playerIndex].getmapX() == 4 && players[playerIndex].getmapY() == 13) { players[playerIndex].location = chosenRoom = 5; }
				Update();
			}
		}
		if (wParam == VK_DOWN){
			if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX() + 1)
				+ players[playerIndex].getmapY() + 2] == 'O') {
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				players[playerIndex].setY(players[playerIndex].getmapY() + 1);
				if (!(players[playerIndex].getNumberOfMoves())) {
					playerIndex++;
					playerIndex %= numberOfPlayers;
				}
				Update();
			}else if (players[playerIndex].getNumberOfMoves() && players[playerIndex].map[26 * (players[playerIndex].getmapX() + 1)
				+ players[playerIndex].getmapY() + 2] == 'E') {
				players[playerIndex].setY(players[playerIndex].getmapY() + 2);//replace with middle of room
				players[playerIndex].setNumberOfMoves(0);
				if (players[playerIndex].getmapX() == 19 && players[playerIndex].getmapY() == 9) { players[playerIndex].location = chosenRoom = 1; }
				else if (players[playerIndex].getmapX() == 15 && players[playerIndex].getmapY() == 19) { players[playerIndex].location = chosenRoom = 2; }
				else if (players[playerIndex].getmapX() == 8 && players[playerIndex].getmapY() == 18) { players[playerIndex].location = chosenRoom = 7; }
				Update();
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		// OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		switch (players[playerIndex].location) {
		case 1:
			if (GET_X_LPARAM(lParam) > 477 && GET_Y_LPARAM(lParam) > 203 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 226 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 477 && GET_Y_LPARAM(lParam) > 410 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 443 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 408 && GET_Y_LPARAM(lParam) > 364 && GET_X_LPARAM(lParam)
				< 431 && GET_Y_LPARAM(lParam) < 397 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 408 && GET_Y_LPARAM(lParam) > 249 && GET_X_LPARAM(lParam)
				< 431 && GET_Y_LPARAM(lParam) < 282 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}
			Update();
			break;
		case 2:// billiard room
			if (GET_X_LPARAM(lParam) > 385 && GET_Y_LPARAM(lParam) > 433 && GET_X_LPARAM(lParam)
				< 408 && GET_Y_LPARAM(lParam) < 456 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 293 && GET_Y_LPARAM(lParam) > 548 && GET_X_LPARAM(lParam)
				< 316 && GET_Y_LPARAM(lParam) < 581 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}
			Update();
			break;
		case 3:// conservatory
			if (GET_X_LPARAM(lParam) > 475 && GET_Y_LPARAM(lParam) > 455 && GET_X_LPARAM(lParam)
				< 500 && GET_Y_LPARAM(lParam) < 470 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) < 155 && GET_Y_LPARAM(lParam) < 180 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(132);
				players[playerIndex].setmapY(180);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = 8;
			}
			Update();
			break;
		case 4: // dining room
			if (GET_X_LPARAM(lParam) > 315 && GET_Y_LPARAM(lParam) > 225 && GET_X_LPARAM(lParam)
				< 340 && GET_Y_LPARAM(lParam) < 260 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 220 && GET_Y_LPARAM(lParam) > 180 && GET_X_LPARAM(lParam)
				< 250 && GET_Y_LPARAM(lParam) < 210 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}
			Update();
			break;
		case 5:// hall
			if (GET_X_LPARAM(lParam) > 130 && GET_Y_LPARAM(lParam) > 385 && GET_X_LPARAM(lParam)
				< 160 && GET_Y_LPARAM(lParam) < 420 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 200 && GET_Y_LPARAM(lParam) > 290 && GET_X_LPARAM(lParam)
				< 230 && GET_Y_LPARAM(lParam) < 440 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}
			Update();
			break;
		case 6:// kitchen
			if (GET_X_LPARAM(lParam) > 430 && GET_Y_LPARAM(lParam) > 130 && GET_X_LPARAM(lParam)
				< 465 && GET_Y_LPARAM(lParam) < 165 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) < 190 && GET_Y_LPARAM(lParam) > 400 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(86);
				players[playerIndex].setmapY(433);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = 9;
			}
			Update();
			break;
		case 7:// library
			if (GET_X_LPARAM(lParam) > 290 && GET_Y_LPARAM(lParam) > 500 && GET_X_LPARAM(lParam)
				< 330 && GET_Y_LPARAM(lParam) < 535 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 175 && GET_Y_LPARAM(lParam) > 175 && GET_X_LPARAM(lParam)
				< 210 && GET_Y_LPARAM(lParam) < 210 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}
			Update();
			break;
		case 8:// lounge
			if (GET_X_LPARAM(lParam) > 175 && GET_Y_LPARAM(lParam) > 175 && GET_X_LPARAM(lParam)
				< 210 && GET_Y_LPARAM(lParam) < 210 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 475 && GET_Y_LPARAM(lParam) > 435 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(523);
				players[playerIndex].setmapY(456);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = 3;
			}
			Update();
			break;
		case 9:// study
			if (GET_X_LPARAM(lParam) > 131 && GET_Y_LPARAM(lParam) > 430 && GET_X_LPARAM(lParam) 
				< 159 && GET_Y_LPARAM(lParam) < 460 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(GET_X_LPARAM(lParam));
				players[playerIndex].setmapY(GET_Y_LPARAM(lParam));
				players[playerIndex].setNumberOfMoves(players[playerIndex].getNumberOfMoves() - 1);
				if (!players[playerIndex].getNumberOfMoves()) {
					playerIndex++;
					playerIndex %= 6;
				}
			}else if (GET_X_LPARAM(lParam) > 425 && GET_Y_LPARAM(lParam) < 200 && players[playerIndex].getNumberOfMoves()) {
				players[playerIndex].setmapX(477);
				players[playerIndex].setmapY(134);
				players[playerIndex].setNumberOfMoves(0);
				players[playerIndex].location = chosenRoom = 6;
			}
			Update();
			break;
		}
		return 0;
	case WM_LBUTTONUP:
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
	case WM_SIZE:
		Resize();
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}