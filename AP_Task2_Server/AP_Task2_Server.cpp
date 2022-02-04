#pragma once
//pre-processor directive with method name to run based on client/server
#define current server

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"
#include "Comms.h"
#include "Client.h"
#include "Server.h"

using namespace std;

int client(Comms comms) {
	Client client;

	//check client socket is okay
	client.clientSocket = comms.CheckSocket(client.clientSocket);
	if (client.clientSocket == INVALID_SOCKET) {
		return 0;
	}

	//connect to client
	if (client.Connect(comms.port) != true) {
		return 0;
	}

	//send and receive
	while (1) {
		if (comms.Send(client.clientSocket) != true) {
			break;
		}
		if (comms.Receive(client.clientSocket) != true) {
			break;
		}
	}
}

int server(Comms comms) {
	Server server;

	//check server socket is okay
	server.serverSocket = comms.CheckSocket(server.serverSocket);
	if (server.serverSocket == INVALID_SOCKET) {
		return 0;
	}

	//bind
	if (server.Bind(comms.port) != true) {
		return 0;
	}

	//listen for connections
	server.Listen();

	//find connections information
	if (server.FindConnection() != true) {
		return 0;
	}

	//receive first and then send
	while (1) {
		if (comms.Receive(server.acceptSocket) != true) {
			break;
		}
		if (comms.Send(server.acceptSocket) != true) {
			break;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	//Declare new instances of comms and client
	Comms comms;

	//initialise wsaData
	WSADATA wsaData{};

	//fetch winsock dll
	bool fetchSuccessful = comms.FetchDll(wsaData);
	if (fetchSuccessful != true) {
		return 0;
	}

	//run client/server based on what's configured
	current(comms);

	system("pause");
	WSACleanup();
	return 0;
}
