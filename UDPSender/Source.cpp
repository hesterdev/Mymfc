#pragma comment(lib,"ws2_32.lib")
#pragma warning (disable:4996)
#include<stdio.h>
#include<Windows.h>

int main(int argc, char**argv) {
	if (argc < 2) {
		system("pause");
		return 1;
	}

	WSADATA wsaData;
	SOCKET sendingSocket;
	SOCKADDR_IN receiverAddr;
	int port = 5150;

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sendingSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(port);
	receiverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);

	while (1) {
		char buffer[1024] = "\0";
		printf("Input message\n");
		scanf("%s", buffer);
		if (strcmp(buffer, "bye") == 0) {
			break;
		}
		int ret = sendto(sendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&receiverAddr, sizeof(receiverAddr));
		if (ret != SOCKET_ERROR) {
			int len = sizeof(receiverAddr);
			ret = recvfrom(sendingSocket, buffer, sizeof(buffer), 0, (SOCKADDR*)&receiverAddr, &len);
			if (ret != SOCKET_ERROR) {
				printf("received from server: %s\n", buffer);
			}

		}
	}
	closesocket(sendingSocket);
	WSACleanup();

	puts("Done");
	system("pause");
	return 0;
}