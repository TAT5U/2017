/*2017-06-13
	狩野 達哉
		クライアントサンプルプログラム*/

/*****インクルード*****/
#include<stdio.h>
#include<winsock2.h>
/**********************/

/**************リンカ**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/

int main(void)
{
	//変数宣言
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[256];

	//起動時
	printf("クライアント起動中・・・\n");

	//winsock2(Windows Sockketの略)の初期化
	//winsockを利用するために必要な初期化関数
	//winsockの利用時は必ず呼び出す必要がある
	//プログラムの先頭で一度だけ行う
	//第一引数 : 使用するWindowsソケットのバージョン情報
	//			 MAKEWORD()は2つの数値を結合して
	//			 2バイトのデータを作成する(0x0200と同じ)
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	//ソケットの作成
	//第一引数 : int型のアドレスファミリ(OSI 第4層トランスポート層)
	//			 例) AF_INET == IPv4アドレスをサポートするように設定
	//第二引数 : 作成するソケットの種類
	//			 TCPやUDPといった通信上の手順を指定
	//			 SOCK_STREAMはTCPを使用し、アドレスファミリは
	//			 IPv4(AF_INET)か、IPv6(AF_INET6)を使用する
	//第三引数 : 使用するプロトコルを記述、ゼロはTCPを指す
	//			 なおアドレスファミリは第二引数と同じ条件
	//			 かつ、第二引数はSOCK_STREAMである必要がある
	//戻値 : エラーコード(失敗するとINVALID_COCKETを返す)
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//エラー処理
		fprintf(stderr, "socketエラー\n");
		exit(1);
	}

	//接続先指定用構造体の準備
	//サーバ側の情報
	//IPアドレス(IPv4)
	server.sin_family = AF_INET;

	//ポート番号	
	//第一引数 : ポート番号 ウェルノウンポートと被らない番号
	//戻値		 TCP/IPネットワークによるIPアドレスと同じ規格に変換した値
	server.sin_port = htons(12345);

	//通信相手のサーバのIP青レスを格納
	//第一引数 : 通信相手のIPアドレスの『.』を付けた状態
	//戻値		 エラーコード(失敗するとINADDR_NONEを返す)
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//サーバに接続
	//第一引数 : 作成したソケット
	//第二引数 : サーバの接続情報
	//第三引数 : サーバのサイズ
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		//エラー処理
		fprintf(stderr, "connectエラー\n");
		exit(1);
	}

	//起動成功時
	printf("起動成功!\n");

	while (1)
	{
		//サーバからデータを受信
		//第一引数 : サーバから受け取ったデータを格納する変数
		//第二引数 : 
		//第三引数 : 受け取ったデータの文字数(バイト)
		memset(buf, 0, sizeof(buf));

		//メッセージ受け取り
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n < 0)
		{
			//エラー処理
			fprintf(stderr, "recvエラー\n");
			exit(1);
		}

		//サーバから受け取ったデータと文字列数を表示する
		printf("%s\n",buf);
	}


	//記述しなければメモリリークになってしまうため必須
	//winsock2の終了処理
	WSACleanup();

	//入力処理
	//何か入力したら終了する
	//サーバから受け取った値を見れるようにするため
	getchar();

	//正常終了
	return 0;
}