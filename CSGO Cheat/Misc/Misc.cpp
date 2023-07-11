#include "Misc.h"

void _Misc::SetClantag(const char* Tag)
{
	auto SendClanTag = reinterpret_cast<void(__fastcall*)(const char* pTag, const char* pName)>(
		Memory.PatternScan(GetModuleHandle(L"engine.dll"), "53 56 57 8B DA 8B F9 FF 15")
		);

	SendClanTag(Tag, Tag);
}

_Misc Misc;