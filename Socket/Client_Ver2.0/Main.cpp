/*2017-07-19
	��� �B��
		�N���C�A���g�T���v���v���O����(���ǔ�)*/

/***************���Ǔ_***************/
//�G���[����
//�T�[�o�Ƃ̐ڑ����؂��܂ŒʐM
/************************************/

/*****�C���N���[�h*****/
//#include<stdio.h>
//#include<winsock2.h>
///**********************/
//
///**************�����J**************/
//#pragma comment(lib,"wsock32.lib")
/**********************************/

#include "Client.h"

int main(void)
{
	//�ϐ��錾
	//WSADATA wsaData;
	//struct sockaddr_in server;
	//SOCKET sock;
	//char buf[512];

	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	//server.sin_family = AF_INET;
	//server.sin_port = htons(12345);
	//server.sin_addr.S_un.S_addr = INADDR_ANY;

	//bind(sock, (struct sockaddr *)&server, sizeof(server));

	//memset(buf, 0, sizeof(buf));

	//recv(sock, buf, sizeof(buf), 0);

	//printf("%s\n", buf);

	//closesocket(sock);


	Client *client = new Client();
	client->InitializeSocket();

	for (int i = 0; i < 10; i++)
	{
		printf("%s\n", client->GetData());
	}

	client->CloseSocket();

	////�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	////winsock2�̏I������
	//WSACleanup();

	//���͏���
	//�������͂�����I������
	//�T�[�o����󂯎�����l�������悤�ɂ��邽��
	//getchar();

	//����I��
	return 0;
}