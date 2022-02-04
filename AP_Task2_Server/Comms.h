#pragma once
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"

using namespace std;

class Comms
{
public:
	Comms() {};
	int port = 55555;
	int byteCount = SOCKET_ERROR;
	bool FetchDll(WSADATA wsaData);
	SOCKET CheckSocket(SOCKET csSocket);
	bool Send(SOCKET socket);
	bool Receive(SOCKET socket);
private:
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	char buffer[200];
	char receiveBuffer[200] = "";
};

