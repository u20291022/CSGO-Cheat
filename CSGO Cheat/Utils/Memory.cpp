#include "Memory.h"

std::vector<uint8_t> _Memory::PatternToBytes(const char* Pattern)
{
	// Example: A1 ? ? 5E 8B or A1 ?? ?? 5E 8B

	std::vector<uint8_t> Bytes;

	char* FirstSymbol = (char*)Pattern;
	char* LastSymbol = (char*)Pattern + strlen(Pattern);

	for (char* CurrentSymbol = FirstSymbol; CurrentSymbol < LastSymbol; CurrentSymbol++)
	{
		if (*CurrentSymbol == ' ' || *CurrentSymbol == '?')
		{
			CurrentSymbol++;
			Bytes.push_back(-1);
			continue;
		}
		else
		{
			int Byte = strtol(CurrentSymbol, &CurrentSymbol, 16);
			Bytes.push_back(Byte);
		}
	}

	return Bytes;
}

uint8_t* _Memory::PatternScan(void* Module, const char* Pattern)
{
	PIMAGE_DOS_HEADER DosHeader = (PIMAGE_DOS_HEADER)Module;
	PIMAGE_NT_HEADERS NTHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)Module + DosHeader->e_lfanew);

	std::vector<uint8_t> PatternBytesVector = this->PatternToBytes(Pattern);
	size_t PatternBytesSize = PatternBytesVector.size();
	uint8_t* PatternBytes = PatternBytesVector.data();

	DWORD ModuleBytesSize = NTHeaders->OptionalHeader.SizeOfImage;
	uint8_t* ModuleBytes = (uint8_t*)Module;

	for (DWORD ModuleBytePosition = 0; ModuleBytePosition < ModuleBytesSize - PatternBytesSize; ModuleBytePosition++)
	{
		bool Found = true;

		for (DWORD PatternBytePosition = 0; PatternBytePosition < PatternBytesSize; PatternBytePosition++)
		{
			if (PatternBytes[PatternBytePosition] != -1 &&
				ModuleBytes[ModuleBytePosition + PatternBytePosition] != PatternBytes[PatternBytePosition])
			{
				Found = false;
				break;
			}
		}

		if (Found)
		{
			return ModuleBytes + ModuleBytePosition;
		}
	}

	return nullptr;
}

_Memory Memory;