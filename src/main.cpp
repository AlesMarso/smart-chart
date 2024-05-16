#include "Application.h"

#include <iostream>
#include <exception>

int main()
{
	try
	{
		Application::Init(GetModuleHandle(nullptr));
		Application::Run(GetModuleHandle(nullptr));
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}