#include <Windows.h>
#include <vector>

class _Memory
{
public:
	uint8_t* PatternScan(void* Module, const char* Pattern);

private:
	std::vector<uint8_t> PatternToBytes(const char* Pattern);
};

extern _Memory Memory;