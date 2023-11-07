#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <thread>

const short port = 7778;

SOCKET sock;

void SendWork()
{
	char buf[256] = { 0, };
	int iLen = 0;

	while (true)
	{
		int iSendByte;
		ZeroMemory(buf, sizeof(char) * 256);
		fgets(buf, 256, stdin);
		if (buf[0] == '\n') break;

		iLen = strlen(buf)+1;
		iSendByte = send(sock, buf, iLen, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			break;
		}
		printf("[����] : %s", buf);

	}
}

int main() //main thread
{
	//���� �ʱ�ȭ
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	//IP                      TCP
	sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.126");
	sa.sin_port = htons(port);
	int result = connect(sock, (SOCKADDR*)&sa, sizeof(sa));
	if (result == 0)
	{
		printf("���� ���� ip=%s, Port:%d �߽��ϴ�.\n",
			inet_ntoa(sa.sin_addr),
			ntohs(sa.sin_port));
	}
	else
	{
		printf("���� ���� ip=%s, Port:%d �Ұ�, ������.\n",
			inet_ntoa(sa.sin_addr),
			ntohs(sa.sin_port));
	}
	//thread
	std::thread sendThread(SendWork);
	sendThread.detach();

	while (true)
	{
		char recvBuf[256] = { 0, };
		int recvByte = recv(sock, recvBuf, 256, 0);
		if (recvByte == SOCKET_ERROR) break;
		printf("[����] : %s", recvBuf);
	}

	closesocket(sock);

	//���� ����
	WSACleanup();

	return 0;
}
