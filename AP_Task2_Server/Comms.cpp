#pragma once

#include "Comms.h"
#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iostream"

using namespace std;

bool Comms::FetchDll(WSADATA wsaData) {
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll could not be found." << endl;
		return false;
	}
	else {
		cout << "The Winsock dll was found!" << endl;
		cout << "Status: " << wsaData.szSystemStatus << endl;
		return true;
	}
}

SOCKET Comms::CheckSocket(SOCKET csSocket) {
	csSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (csSocket == INVALID_SOCKET) {
		cout << "Socket is invalid: " << WSAGetLastError() << endl;
		WSACleanup();
		return csSocket;
	}
	else {
		cout << "Socket is OK!" << endl;
		return csSocket;
	}
}

bool Comms::Send(SOCKET socket) {
	cout << "Enter your message: ";
	cin.getline(buffer, 200);

	byteCount = send(socket, buffer, 200, 0);
	if (byteCount == SOCKET_ERROR) {
		cout << "Could not send the message: " << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "Sent!" << endl;
		if (strcmp(buffer, "QUIT") == 0) {
			return false;
		}
		else {
			return true;
		}
	}
}

bool Comms::Receive(SOCKET socket) {
	byteCount = recv(socket, receiveBuffer, 200, 0);
	if (byteCount == 0 || byteCount == WSAECONNRESET) {
		cout << "Connection Closed :(" << endl;
		return false;
	}
	if (byteCount < 0) {
		cout << "Error receiving message: " << WSAGetLastError() << endl;
		return false;
	}
	else {
		cout << "Received: " << receiveBuffer << endl;
	}

	if (strcmp(receiveBuffer, "QUIT") == 0) {
		return false;
	}
	else {
		return true;
	}
}