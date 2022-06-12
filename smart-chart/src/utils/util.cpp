#include "util.h"

char* utils::resource::GetResString(uint32_t resid)
{
	char wndClassName[1024] = { 0 };

	LoadString(GetModuleHandle(nullptr), resid, wndClassName, 1024);

	return wndClassName;
}

