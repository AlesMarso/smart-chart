#include <iostream>

#include "gui/SC_MDIClientWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	gui::SC_MDIClientWindow testWindow;

	if (!testWindow.Init(hInstance))
		return -1;

	if (!testWindow.Create("Smart Chart", nullptr))
		return -1;
	
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		if (msg.message == WM_QUIT)
			return static_cast<int>(msg.wParam);

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}
