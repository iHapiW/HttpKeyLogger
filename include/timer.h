#ifndef TIMER_H
#define TIMER_H

#include "shared.h"

void WINAPI _flusher(LPVOID data, DWORD high, DWORD low);
DWORD WINAPI handleTimer();

#endif // TIMER_H