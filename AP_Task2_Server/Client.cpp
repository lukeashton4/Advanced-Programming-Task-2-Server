#include "Client.h"

bool Client::Connect(int port) {
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Failed to connect" << endl;
		WSACleanup();
		return false;
	}
	else {
		cout << "Connection is OK!" << endl;
		cout << "Start sending and receiving messages :)" << endl;
		return true;
	}
}