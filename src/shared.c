#include "shared.h"

void flush()
{
#ifdef DEBUG
    for (int i = 0; i < BUFFSIZE; ++i)
    {
        if (Buffer[i] == 0x00)
            break;
        printf("%d ", Buffer[i]);
    }
    printf("\n");
#endif
    Index = 0;
    for (int i = 0; i < BUFFSIZE; ++i)
        Buffer[i] = 0x00;
}


#ifdef DEBUG
void handleError(LPCTSTR funcName)
{
    LPVOID msg;
    DWORD err = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&msg,
        0, NULL);

    fprintf(stderr, "%s Failed With Error: %s", funcName, (char*)msg);

    LocalFree(msg);
}
#endif