#include "util.h"

char* utils::resource::GetResString(uint32_t resid)
{
	char* wndClassName = new char[64];

	LoadString(GetModuleHandle(nullptr), resid, wndClassName, 64);

	return wndClassName;
}

