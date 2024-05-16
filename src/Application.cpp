#include "Application.h"

#include <exception>
#include <iostream>

#include <Windows.h>
#include "Window.h"
#include "util.h"
#include "res.h"

void Application::Init(HINSTANCE instance)
{
	if (!glfwInit())
		throw std::exception("GLFW don't initilized");

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

	auto res = main_window_.Create(nullptr, util::GetString(IDS_SMART_CHART_MAIN_WINDOW_NAME));

	if (!res)
		throw std::exception("Not created window!!!");

	MSG msg = { 0 };

	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		if (msg.message == WM_QUIT)
			break;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
