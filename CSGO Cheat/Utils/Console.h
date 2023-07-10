#include <windows.h>

class _Console
{
private:
	HANDLE _out, _in, _err;
	HANDLE _out_bac, _in_bac, _err_bac;

public:
	void Allocate(PVOID Module);
	void Write(const char* Str);
	void Write(int Data);
	void Free();
};

extern _Console Console;