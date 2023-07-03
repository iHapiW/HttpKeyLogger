#ifndef SHARED_H
#define SHARED_H

#ifdef DEBUG
#include <stdio.h>
#endif

#include "Windows.h"

#include "connection.h"

#define BUFFSIZE 16

HANDLE Mutex;
DWORD Buffer[BUFFSIZE];
FILETIME LastFlush;
DWORD Index;

// store's `repr`s size in `size` ( including NULL char ). repr can be NULL ( to get `size` then alloc ) or a buffer containing at least `size` bytes.
void getStrRepr(char* repr, size_t* size);

// Push Buffer to Somewhere and Make Buffer Empty
void flush();

#ifdef DEBUG
void handleError(LPCTSTR funcName);
#endif

#endif // SHARED_H