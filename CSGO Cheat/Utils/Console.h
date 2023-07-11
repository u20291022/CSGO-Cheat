#include <windows.h>
#include <string>

class _Console
{
private:
	HANDLE _out, _in, _err;
	HANDLE _out_bac, _in_bac, _err_bac;
	bool IsAllocated();

public:
	void Allocate();
	void Write(const char* Str, ...);
	void Free();
};

extern _Console Console;