/*2017-07-19
	��� �B��
		�T�[�o�T���v���v���O����(���ǔ�)*/

/***************���Ǔ_***************/
//�G���[����
//�C�ӂ̃��b�Z�[�W�𑗐M�\��
//�����񑗐M�\��
//�I����������
/************************************/

/*****�C���N���[�h*****/
//#include<stdio.h>
//#include<winsock2.h>
//#include<conio.h>
///**********************/
//
///**************�����J**************/
//#pragma comment(lib,"ws2_32.lib")
///**********************************/
//
////�z��̕��������J�E���g����萔
//#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))



#include "Server.h"

//#include "SocketUnit.h"

int main(void)
{
	////�ϐ���錾
	//char buf;
	//WSADATA wsaData;
	//SOCKET sock0;
	//struct sockaddr_in addr;
	//struct sockaddr_in client;
	//int len;
	//int mesSize;
	//SOCKET sock;

	//WSAStartup(MAKEWORD(2, 2), &wsaData);

	//sock = socket(AF_INET, SOCK_DGRAM, 0);

	//addr.sin_family = AF_INET;
	//addr.sin_port = htons(12345);

	//addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//sendto(sock, "HELLO Client!!", 15, 0, (struct sockaddr *)&addr, sizeof(addr));

	//closesocket(sock);

	//////�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	////winsock2�̏I������
	//WSACleanup();

	Server *server = new Server();
	server->InitializeSocket();

	for (int i = 0; i < 10; i++)
	{
		server->SendData("HELLO Client!!");
	}

	server->CloseSocket();


	//SocketUnit *so = new SocketUnit();
	//so->InitializeSocket();
	//so->CloseSocket();

	//����I��
	return 0;
}