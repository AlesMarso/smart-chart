#include "SC_EventContainer.h"

void gui::SC_EventContainer::SetEvent(uint32_t event_id, uint32_t action_id, Event func)
{
    Action action;
    action[action_id] = func;

    m_Container[event_id] = action;
}

bool gui::SC_EventContainer::operator()(uint32_t event_id, uint32_t action_id, HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    if (m_Container.empty())
        return false;

    auto eventIter = m_Container.find(event_id);

    if (eventIter == m_Container.end())
        return false;

    auto actionIter = eventIter->second.find(action_id);

    if (actionIter == eventIter->second.end())
        return false;

    return actionIter->second(hWnd, wParam, lParam);
}
