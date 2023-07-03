#ifndef CONNECTION_H
#define CONNECTION_H

#ifdef DEBUG
#include <stdio.h>
#endif

#include <Windows.h>
#include <winhttp.h>

#include "shared.h"
#include CONFIG

static HINTERNET hSession = NULL;
static HINTERNET hConnect = NULL;

void initSession();
void initConnection();

void sendData(LPSTR buffer, size_t size);

#endif // CONNECTION_H