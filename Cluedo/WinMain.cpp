#include "MainWindow.h"
#include <memory>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	std::unique_ptr<MainWindow> win = std::make_unique<MainWindow>();
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
		}
	}
	return 0;
}
