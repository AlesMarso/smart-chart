#pragma once

#include <Windows.h>

#include <functional>
#include <map>

#define BIND_EVENT(funcname) std::bind(&funcname, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

namespace gui
{
	using Event = std::function<bool(HWND, WPARAM, LPARAM)>;
	using Action = std::map<uint32_t, Event>;

	class SC_EventContainer
	{
	public:
		SC_EventContainer() = default;
		~SC_EventContainer();

		void SetEvent(uint32_t, uint32_t, Event);

		bool operator()(uint32_t, uint32_t, HWND, WPARAM, LPARAM);

	private:
		std::map<uint32_t, Action> m_Container;
	};
}
