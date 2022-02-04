#include "Server.h"

bool Server::Bind(int port) {
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "Server bind failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return false;
	}
	else {
		cout << "Server bind is OK!" << endl;
		return true;
	}
}

void Server::Listen() {
	if (listen(serverSocket, 1) == SOCKET_ERROR)
		cout << "Error whilst listening on socket: " << WSAGetLastError() << endl;
	else
		cout << "Listen successful, waiting for connections..." << endl;
}

bool Server::FindConnection() {
	fromlen = sizeof(socket_type);
	retval = getsockopt(serverSocket, SOL_SOCKET, SO_TYPE, (char*)&socket_type, &fromlen);
	fromlen = sizeof(from);
	acceptSocket = accept(serverSocket, (SOCKADDR*)&from, &fromlen);

	if (acceptSocket == INVALID_SOCKET) {
		cout << "Accept socket failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	retval = getnameinfo((SOCKADDR*)&from,
		fromlen,
		hoststr,
		NI_MAXHOST,
		servstr,
		NI_MAXSERV,
		NI_NUMERICHOST | NI_NUMERICSERV);
	if (retval != 0) {
		cout << "Couldn't retreive incoming connection details: " << retval << endl;
		WSACleanup();
		return false;
	}
	cout << "Accepted connection from: " << hoststr << ". Port number: " << servstr << endl;
	return true;
}
