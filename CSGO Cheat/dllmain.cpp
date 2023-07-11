#include <windows.h>
#include "Utils/Console.h"


DWORD WINAPI OnAttach(LPVOID Module)
{
#ifdef _DEBUG
    Console.Allocate();
#endif // DEBUG

    Console.Write("Initialization.");
    {

    }
    Console.Write("All done.");

    while (!GetAsyncKeyState(VK_DELETE));

    Console.Free();
    FreeLibraryAndExitThread((HMODULE)Module, 1);
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD ReasonForCall, LPVOID Reserved)
{
    switch (ReasonForCall)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, 0, OnAttach, Module, NULL, nullptr);

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

