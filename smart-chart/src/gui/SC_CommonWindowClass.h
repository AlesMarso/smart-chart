#pragma once

#include <Windows.h>
#include <cstdint>
#include <functional>
#include <map>

#include "resource.h"
#include "utils/util.h"

#include "SC_EventContainer.h"

#define CONTROL_ID (LOWORD(wParam))
#define ACTION_ID (HIWORD(wParam))

namespace gui
{
	class SC_CommonWindowClass
	{
	public:
		SC_CommonWindowClass();
		virtual ~SC_CommonWindowClass();

	public:
		HWND GetHWND() const;
		HINSTANCE GetInstance() const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		void SetHWND(HWND);
		void SetEvent(uint32_t, uint32_t, Event);

		virtual const char* GetWindowClassName() = 0;
		virtual const char* GetWindowTitle() = 0;

	public:
		virtual bool Init(HINSTANCE) = 0;
		virtual bool Create(HWND) = 0;
		virtual bool OnPaint(HWND, WPARAM, LPARAM) = 0;
		virtual bool OnCreate(HWND, WPARAM, LPARAM) = 0;
		virtual bool OnSize(HWND, WPARAM, LPARAM) = 0;
		virtual bool OnClose(HWND, WPARAM, LPARAM) = 0;
		virtual bool OnDestroy(HWND, WPARAM, LPARAM) = 0;
		virtual bool OnNcDestroy(HWND, WPARAM, LPARAM) = 0;

	protected:
		virtual LRESULT MessageHandle(HWND, UINT, WPARAM, LPARAM);

	protected:
		char* m_WindowClassName;
		char* m_WindowTitle;

	private:
		HWND		m_hWnd;
		HINSTANCE	m_hInstance;

		uint32_t	m_Width;
		uint32_t	m_Height;

		SC_EventContainer m_Events;
	};
}
