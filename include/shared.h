#ifndef SHARED_H
#define SHARED_H

#ifdef DEBUG
#include <stdio.h>
#endif

#include "Windows.h"

#define BUFFSIZE 16

HANDLE Mutex;
DWORD Buffer[BUFFSIZE];
FILETIME LastFlush;
DWORD Index;

void flush();

#ifdef DEBUG
void handleError(LPCTSTR funcName);
#endif

#endif // SHARED_H