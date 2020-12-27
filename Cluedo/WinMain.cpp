#include "MainWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	MainWindow* win = new MainWindow();
	if (!win->Create(L"Cluedo", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}
	win->OnCreate();
	ShowWindow(win->Window(), nCmdShow);
	// Run the message loop.
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}else {		
			//win->Update();
		}
	}
	delete win;
	return 0;
}