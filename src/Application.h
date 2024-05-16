#pragma once

#include <GLFW/glfw3.h>
#include <gl/GL.h>

#include "Window.h"

class Application
{
public:
	Application() = default;
	~Application() = default;

	static void Init(HINSTANCE instance);
	static void Run(HINSTANCE instance);
};
