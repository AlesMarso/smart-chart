#include "Application.h"

#include <exception>
#include <iostream>

#include <Windows.h>
#include "Window.h"
#include "util.h"
#include "res/resource.h"

void Application::Init(HINSTANCE instance)
{
#ifdef _DEBUG
	std::cout << "Initilized is completed!" << std::endl;
#endif
}

void Application::Run(HINSTANCE instance)
{
#ifdef _DEBUG
	std::cout << "Run application" << std::endl;
#endif // _DEBUG

	chart::wnd::Window main_window_;

	if(!main_window_.Register(instance))
		throw std::exception("Fault register window!");

	if (main_window_.Create(nullptr, util::GetString(IDS_SMART_CHART_MAIN_WINDOW_NAME))) {
		MSG msg = { 0 };

		while (GetMessage(&msg, main_window_.GetHWND(), 0, 0) > 0)
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
