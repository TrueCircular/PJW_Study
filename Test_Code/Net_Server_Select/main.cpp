#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <list>

const short port = 7778;
int g_time = 0;
std::list<SOCKET> g_userList;

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsa;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (result != 0) return 1;
	//IP                       TCP
	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);

	////�ͺ�� �Ҵ�
	//u_long on = TRUE;
	//ioctllistenSocket(listenSock, FIONBIO, &on);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);

	result = bind(listenSock, (SOCKADDR*)&sa, sizeof(sa));
	if (result == SOCKET_ERROR) return 1;
	result = listen(listenSock, SOMAXCONN);
	if (result == SOCKET_ERROR) return 1;

	SOCKADDR_IN clientAddr;
	SOCKET clientSock;

	printf("���� ON\n");
	std::clock_t start = std::clock();

	FD_SET recvSet;
	FD_SET sendSet;
	FD_SET execptSet;
	TIMEVAL timeout;

	while (1)
	{
		FD_ZERO(&recvSet);
		FD_SET(listenSock, &recvSet);
		result = select(0, &recvSet, &sendSet, &execptSet, &timeout);

		if (result == SOCKET_ERROR) break;

		if (FD_ISSET(listenSock, &recvSet))
		{
			int addrLen = sizeof(clientAddr);
			clientSock = accept(listenSock, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSock == SOCKET_ERROR)
			{
				int iError = WSAGetLastError();

				if (iError != WSAEWOULDBLOCK)
				{
					break;
				}
			}
			else
			{
				g_userList.push_back(clientSock);

				printf("Ŭ���̾�Ʈ ���� IP : %s PORT : %d\n", inet_ntoa(clientAddr.sin_addr),
					ntohs(clientAddr.sin_port));
			}

			for (std::list<SOCKET>::iterator iter = g_userList.begin(); iter != g_userList.end();)
			{
				SOCKET cSock = *iter;
				char reBuf[256] = { 0, };
				int recvByte = recv(cSock, reBuf, 256, 0);
				if (recvByte == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					if (iError != WSAEWOULDBLOCK)
					{
						iter = g_userList.erase(iter);
						continue;
					}
				}
				else
				{
					if (recvByte == 0 || recvByte == SOCKET_ERROR)
					{
						iter = g_userList.erase(iter);
						continue;
					}

					printf("���� PORT : %d ���� �޼��� : %s\n", ntohs(clientAddr.sin_port), reBuf);
					int iLen = strlen(reBuf);

					for (std::list<SOCKET>::iterator iterSend = g_userList.begin();
						iterSend != g_userList.end(); iterSend++)
					{
						SOCKET sSock = *iterSend;
						int sendByte = send(sSock, reBuf, iLen, 0);

						if (sendByte == SOCKET_ERROR)
						{
							int tError = WSAGetLastError();
							if (tError != WSAEWOULDBLOCK) break;
						}
					}
				}
				iter++;
			}
		}

		
	}

	closesocket(listenSock);

	//���� ����
	WSACleanup();

	return 0;
}