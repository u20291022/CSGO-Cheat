#include <windows.h>
#include "Utils/Console.h"

DWORD WINAPI OnAttach(LPVOID Module)
{
    Console.Allocate(Module);

    Console.Write("Hello, world!");
    Console.Write("I'm new here!");
    Console.Write(5000);

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

