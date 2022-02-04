#pragma once
#include "Comms.h"
class Server :
    public Comms
{
public:
    SOCKADDR_STORAGE from;
    int retval, fromlen, socket_type;
    char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
    SOCKET serverSocket, acceptSocket;
    bool Bind(int port);
    void Listen();
    bool FindConnection();
private:
    sockaddr_in service;
};

