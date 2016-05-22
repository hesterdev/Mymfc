#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")


#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>

int main(int argc, char**argv) {
	if (argc <= 1) {
		printf("Usage: TCPClient <Server_IP_Address>.\n");
		system("pause");
		return 0;
	}

	WSAData wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0) {//不等于0就是失败了
		printf("WSAStartup failed with error %d\n", ret);
		return 0;
	}

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		printf("socket failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	SOCKADDR_IN serverAddr;
	int port = 5000;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port); //本机字节顺序 转换为网络字节顺序
	serverAddr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
	printf("We are trying to connect to %s:%d...\n", inet_ntoa(serverAddr.sin_addr), port);

	int isSuccess = connect(s, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (isSuccess == SOCKET_ERROR) {
		printf("connect failed with error %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 0;
	}

	printf("Our connection succeeded.\n");
	printf("We will now try to send a hello message.\n");
	isSuccess = send(s, "hello", 5, 0);
	if (isSuccess == SOCKET_ERROR) {
		printf("Send failed with error %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 0;
	}

	printf("We successfully sent %d bytes.\n", isSuccess);


	puts("Done");
	system("pause");
	return 0;
}