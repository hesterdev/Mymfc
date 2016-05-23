#pragma comment(lib,"ws2_32.lib")

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int main() {
	WSADATA wsaData;
	int Ret;

	Ret = WSAStartup(MAKEWORD(2, 2)/*2.2版本*/, &wsaData);
	if (Ret != 0) {
		printf("Error: WSAStartup failed with error %d\n", Ret);
	}
	else {
		// 进一步检查, 看看是不是2.2 版本
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
			printf("Error: not winsock 2.2\n");
			WSACleanup();
			return 1;
		}
	}
	SOCKET receiveSocket;
	receiveSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (receiveSocket == INVALID_SOCKET) {
		printf("ERROR: socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN receiveAddr;
	int port = 5150;
	receiveAddr.sin_family = AF_INET;
	receiveAddr.sin_port = htons(port);
	receiveAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	Ret = bind(receiveSocket, (SOCKADDR*)&receiveAddr, sizeof(receiveAddr));
	if (Ret == SOCKET_ERROR) {
		printf("ERROR: bind failed with error: %d\n", WSAGetLastError());
		closesocket(receiveSocket);
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN senderAddr;
	int len;

	len = sizeof(senderAddr);

	while (1) {
		char buffer[1024] = "\0";
		printf("waiting for message from others...\n");
		Ret = recvfrom(receiveSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&senderAddr, &len);
		if (Ret == SOCKET_ERROR) {
			printf("Error: recvfrom failed with error %d\n", WSAGetLastError());
			closesocket(receiveSocket);
			WSACleanup();
			return 1;
		}
		else {
			printf("Received datagram from %s -- %s\n", inet_ntoa(senderAddr.sin_addr),buffer);
			sendto(receiveSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&senderAddr, len);
		}
		Sleep(500);
	}
	closesocket(receiveSocket);
	WSACleanup();


	puts("Done");
	system("pause");
	return 0;
}
