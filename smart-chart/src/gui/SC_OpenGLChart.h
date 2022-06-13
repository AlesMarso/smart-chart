#pragma once

#include "SC_MDIChildWindow.h"

#include <gl/GLU.h>
#include <gl/GL.h>

namespace gui
{
	class SC_OpenGLChart : public SC_MDIChildWindow
	{
	public:
		SC_OpenGLChart();
		~SC_OpenGLChart();

		bool OnPaint(HWND, WPARAM, LPARAM) override;
		bool OnCreate(HWND, WPARAM, LPARAM) override;
		bool OnSize(HWND, WPARAM, LPARAM) override;
		bool OnEraseBackground(HWND, WPARAM, LPARAM) override;

		void Render(HDC);

	private:
		HGLRC m_OGLRenderContext;
	};
}
