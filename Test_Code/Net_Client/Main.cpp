#include <iostream>
#include <WinSock2.h>


const short port = 3738;

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
						//IP                       TCP
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//�ͺ�� �Ҵ�
	u_long on = TRUE;
	ioctlsocket(sock, FIONBIO, &on);

	SOCKADDR_IN sa;	
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr("192.168.0.126");
	sa.sin_port = htons(port);
	int result = connect(sock, (SOCKADDR*)&sa, sizeof(sa));

	char buf[256] = "Oliver";
	int iLen = strlen(buf);
	int iSendByte = 0;
	send(sock, buf, iLen, 0);

	while (true)
	{
		iSendByte = 0;
		ZeroMemory(buf, sizeof(char) * 256);
		printf("���� ������ �Է� : ");
		fgets(buf, 256, stdin);
		if (buf[0] == '\n') break;
		iLen = strlen(buf) - 1;
		iSendByte = send(sock, buf, iLen, 0);

		char recvBuf[256] = { 0, };
		int iRecvByte = recv(sock, recvBuf, 256, 0);
		printf("���� ���� : %s\n", recvBuf);
	}

	closesocket(sock);

	//���� ����
	result = WSACleanup();

	return result;
}
