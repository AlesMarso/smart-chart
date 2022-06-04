#include <iostream>

#include "gui/SC_CommonWindowClass.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	gui::SC_CommonWindowClass testWindow;

	if (testWindow.Init(hInstance, "Smart Chart"))
		return testWindow.Run();

	return 0;
}
