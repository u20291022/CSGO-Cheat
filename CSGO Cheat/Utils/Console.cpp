#include "Console.h"

bool _Console::IsAllocated()
{
	return this->_out && this->_in && this->_err;
}

void _Console::Allocate()
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

void _Console::Write(const char* Str, ...)
{
	if (!this->IsAllocated())
	{
		return;
	}

	std::string Message;

	va_list Arguments;
	va_start(Arguments, Str);

	// length + 1 because we have '\0' at string end: "hello\0"
	size_t Length = vsnprintf(0, 0, Str, Arguments) + 1;
	Message.resize(Length);

	vsnprintf(&Message[0], Length, Str, Arguments);

	va_end(Arguments);

	WriteConsoleA(this->_out, Message.c_str(), strlen(Message.c_str()), nullptr, NULL);
	WriteConsoleA(this->_out, "\n", 1, nullptr, NULL);

}

void _Console::Free()
{
	if (this->IsAllocated())
	{
		FreeConsole();

		SetStdHandle(STD_OUTPUT_HANDLE, this->_out_bac);
		SetStdHandle(STD_INPUT_HANDLE, this->_in_bac);
		SetStdHandle(STD_ERROR_HANDLE, this->_err_bac);
	}
}

_Console Console;