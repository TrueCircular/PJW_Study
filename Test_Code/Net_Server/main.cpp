#include <iostream>
#include <WinSock2.h>

const short port = 3738;

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsa;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (result != 0) return 1;
	//IP                       TCP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	//�ͺ�� �Ҵ�
	u_long on = TRUE;
	ioctlsocket(sock, FIONBIO, &on);

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);

	result = bind(sock,(SOCKADDR*)&sa, sizeof(sa));
	if (result == SOCKET_ERROR) return 1;
	result = listen(sock, SOMAXCONN);
	if (result == SOCKET_ERROR) return 1;

	SOCKADDR_IN clientAddr;
	SOCKET clientsock;

	printf("���� ON");

	while (1)
	{
		int addrLen = sizeof(clientAddr);
		clientsock = accept(sock, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientsock == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();

			if (iError != WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			printf("Ŭ���̾�Ʈ ���� IP : %s PORT : %d\n", inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port));

			while (1)
			{
				char buf[256] = { 0, };
				int iRecvByte = recv(clientsock, buf, 256, 0);

				if (iRecvByte == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();

					if (iError != WSAEWOULDBLOCK)
					{
						break;
					}
				}
				else
				{
					if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR)
					{
						break;
					}

					int iLen = strlen(buf) -1;
					int iSend = send(clientsock, buf, iLen, 0);

					printf("���� ������ : %s \n", buf);
				}
			}
			closesocket(clientsock);
			printf("Ŭ���̾�Ʈ ���� ���� IP : %s PORT: %d\n", inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port));
			break;
		}
	}
	closesocket(sock);

	//���� ����
	result = WSACleanup();

	return result;
}