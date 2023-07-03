#include "timer.h"

void WINAPI _flusher(LPVOID data, DWORD high, DWORD low)
{
    DWORD waitRes = WaitForSingleObject(Mutex, INFINITE);
    switch (waitRes)
    {
    case WAIT_OBJECT_0:
        __try
        {
            FILETIME now;
            GetSystemTimeAsFileTime(&now);
            if (now.dwLowDateTime - LastFlush.dwLowDateTime >= REFRESHTIME * 10'000'000L && Buffer[0] != 0x00)
            {
                memcpy(&LastFlush, &now, sizeof(FILETIME));
                flush();
            }
        }
        __finally
        {
            if (!ReleaseMutex(Mutex))
#ifdef DEBUG
                handleError("ReleaseMutex");
#endif
        }
    }
}


DWORD WINAPI handleTimer()
{
    while (TRUE)
    {
        // Creating The Timer.
        HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);
        if (timer == NULL)
        {
#ifdef DEBUG
            handleError("CreateWaitableTimer");
#endif
            continue;
        }

        // Starting the timer immediately
        LARGE_INTEGER dueTime;
        ZeroMemory(&dueTime, sizeof(LARGE_INTEGER));
        if (!SetWaitableTimer(timer, &dueTime, 1000, _flusher, NULL, 0))
        {
#ifdef DEBUG
            handleError("SetWaitableTimer");
#endif
            CancelWaitableTimer(timer);
            CloseHandle(timer);
            continue;
        }

        // Looping over SleepEx, so timer can wakeup asynchronously every second
        while (SleepEx(INFINITE, TRUE)) {};

        break;
    }
}