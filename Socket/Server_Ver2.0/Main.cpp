/*2017-07-19
	狩野 達哉
		サーバサンプルプログラム(改良版)*/

/***************改良点***************/
//エラー処理
//任意のメッセージを送信可能に
//複数回送信可能に
//終了処理実装
/************************************/

/*****インクルード*****/
//#include<stdio.h>
//#include<winsock2.h>
//#include<conio.h>
///**********************/
//
///**************リンカ**************/
//#pragma comment(lib,"ws2_32.lib")
///**********************************/
//
////配列の文字数をカウントする定数
//#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))



#include "Server.h"

//#include "SocketUnit.h"

int main(void)
{
	////変数を宣言
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

	//////記述しなければメモリリークになってしまうため必須
	////winsock2の終了処理
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

	//正常終了
	return 0;
}