#pragma once
#include "Comms.h"
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
class Client :
    public Comms
{
public:
    Client() {};
    SOCKET clientSocket = INVALID_SOCKET;
    bool Connect(int port);
private:
    sockaddr_in clientService;
};

