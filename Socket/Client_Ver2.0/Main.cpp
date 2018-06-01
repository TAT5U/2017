/*2017-07-19
	狩野 達哉
		クライアントサンプルプログラム(改良版)*/

/***************改良点***************/
//エラー処理
//サーバとの接続が切れるまで通信
/************************************/

/*****インクルード*****/
//#include<stdio.h>
//#include<winsock2.h>
///**********************/
//
///**************リンカ**************/
//#pragma comment(lib,"wsock32.lib")
/**********************************/

#include "Client.h"

int main(void)
{
	//変数宣言
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

	////記述しなければメモリリークになってしまうため必須
	////winsock2の終了処理
	//WSACleanup();

	//入力処理
	//何か入力したら終了する
	//サーバから受け取った値を見れるようにするため
	//getchar();

	//正常終了
	return 0;
}