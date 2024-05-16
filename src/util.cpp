#include "util.h"

#include <Windows.h>

namespace util {

	const int MAX_STR_LENGTH = 64;

	const char* GetString(uint32_t id)
	{
		char* str = new char[MAX_STR_LENGTH];

		LoadStringA(GetModuleHandleA(nullptr), id, str, MAX_STR_LENGTH);

		return str;
	}
}