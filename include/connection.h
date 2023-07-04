#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>

#include <Windows.h>
#include <winhttp.h>

#include "shared.h"
#include CONFIG

static HINTERNET hSession = NULL;
static HINTERNET hConnect = NULL;

void initSession();
void initConnection();

void sendData(LPSTR buffer, DWORD size);

#endif // CONNECTION_H