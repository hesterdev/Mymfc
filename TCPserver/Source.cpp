#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")

#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

void main(void) {

	WSADATA wsaData;
	DWORD ret;
	if ((ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		printf("WSAStartup failed with error %d\n", ret);
		return;
	}

	SOCKET ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListeningSocket == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return;
	}

	int port = 5000;

	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(port); // htons  host to online
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(ListeningSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("bind failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		printf("listen failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return;
	}
	printf("We are waiting a connection on port %d. \n", port);
	printf("LIsten(ÕýÔÚ¼àÌý)...\n");

	SOCKADDR_IN ClientAddr;
	int len;
	len = sizeof(SOCKADDR);

	SOCKET NewConnection = accept(ListeningSocket, (SOCKADDR*)&ClientAddr, &len);
	if (NewConnection == INVALID_SOCKET) {
		printf("accept failed with error %d\n", WSAGetLastError());
		return;
	}

	printf("we successfully got a connection from %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));
	closesocket(ListeningSocket);
	printf("we are waiting to receive data\n");


	char DataBuffer[1024];

	if ((ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("recv failed with error %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
	}

	printf("We successfully received %d bytes.\n", ret);
	DataBuffer[ret] = '\0';
	printf("%s\n", DataBuffer);
	printf("We are now going to close the client connection.\n");
	closesocket(NewConnection);
	WSACleanup();


	puts("Done");
	system("pause");
}