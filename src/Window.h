#pragma once

#include <Windows.h>
#include <cstdint>

namespace chart
{
	namespace wnd
	{
		struct WndEventArgs
		{
			HWND hWnd_ = nullptr;
			WPARAM wParam_ = 0;
			LPARAM lParam_ = 0;
		};

		struct WndCommandArgs
		{
			HWND hWnd_ = nullptr;
			WORD loWord_ = -1;
			WORD hiWord_ = -1;
			LPARAM lParam_ = 0;
		};

		class Window
		{
		public:
			Window();
			~Window() = default;

			bool Register(HINSTANCE instance);
			bool Create(HWND parent, const char* name, uint32_t x = CW_USEDEFAULT, uint32_t y = CW_USEDEFAULT, uint32_t width = CW_USEDEFAULT, uint32_t height = CW_USEDEFAULT);
			bool Destroy();

			uint32_t GetX() const;
			uint32_t GetY() const;
			uint32_t GetWidth() const;
			uint32_t GetHeight() const;

			LRESULT OnCreate(const WndEventArgs& args);
			LRESULT OnSize(const WndEventArgs& args);
			LRESULT OnPaint(const WndEventArgs& args);
			LRESULT OnDestroy(const WndEventArgs& args);
			LRESULT OnClose(const WndEventArgs& args);
			LRESULT OnNcDestroy(const WndEventArgs& args);
			LRESULT OnCommand(const WndCommandArgs& args);
			LRESULT OnMenuCommand(const WndEventArgs& args);
			LRESULT OnFileAbout(const WndEventArgs& args);

		protected:
			LRESULT MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			static LRESULT MessageHandlerSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		protected:
			HWND hwnd_;
			WNDCLASSEXA wndClass_;
			HINSTANCE instance_;

			uint32_t x_;
			uint32_t y_;
			uint32_t width_;
			uint32_t height_;
		};
	}
}
