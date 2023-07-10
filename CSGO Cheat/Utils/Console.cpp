#include "Console.h"

void _Console::Allocate(PVOID Module)
{
	this->_out_bac = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_in_bac = GetStdHandle(STD_INPUT_HANDLE);
	this->_err_bac = GetStdHandle(STD_ERROR_HANDLE);

	AllocConsole();

	this->_out = GetStdHandle(STD_OUTPUT_HANDLE);
	this->_in = GetStdHandle(STD_INPUT_HANDLE);
	this->_err = GetStdHandle(STD_ERROR_HANDLE);

	SetConsoleTitle(L"CS:GO Cheat");
}

void _Console::Write(const char* Str)
{
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), Str, strlen(Str), nullptr, NULL);
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, nullptr, NULL);
}

void _Console::Write(int Data)
{
	char* Str = (char*)malloc(1024);
	_itoa_s(Data, Str, 1024, 10);

	this->Write(Str);
}

void _Console::Free()
{
	if (this->_out && this->_in && this->_err) // Check if console was allocated
	{
		FreeConsole();

		SetStdHandle(STD_OUTPUT_HANDLE, this->_out_bac);
		SetStdHandle(STD_INPUT_HANDLE, this->_in_bac);
		SetStdHandle(STD_ERROR_HANDLE, this->_err_bac);
	}
}

_Console Console;