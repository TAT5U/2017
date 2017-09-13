/*2017-06-13
	狩野 達哉
		サーバサンプルプログラム*/

/*****インクルード*****/
#include<stdio.h>
#include<winsock2.h>
#include<conio.h>
/**********************/

/**************リンカ**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/


#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

int main(void)
{
	//変数を宣言
	char buf;
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int mesSize;
	SOCKET sock;

	//起動時
	printf("サーバ起動中・・・\n");

	//winsock2(Windows Sockketの略)の初期化
	//winsockを利用するために必要な初期化関数
	//winsockの利用時は必ず呼び出す必要がある
	//プログラムの先頭で一度だけ行う
	//第一引数 : 使用するWindowsソケットのバージョン情報
	//			 MAKEWORD()は2つの数値を結合して
	//			 2バイトのデータを作成する(0x0200と同じ)
	int status = WSAStartup(MAKEWORD(2, 0), &wsaData);

	//エラー処理
	if (status != 0)
	{
		//仕事で組むなら考慮する必要がある
		switch (status)
		{
			//準備されていない
			case WSASYSNOTREADY:
				break;

			//バージョンが違う
			case WSAVERNOTSUPPORTED:
				break;

			//通信がブロックされている
			case WSAEINPROGRESS:
				break;

			//多重起動されている
			case WSAEPROCLIM:
				break;
		}
	}

	//ソケットの作成
	//ソケットは1つ以上のクライアントと対で初めて通信可能
	//ここで使われる通信プロトコルについては下記で設定
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
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET)
	{
		//エラー処理
		fprintf(stderr, "socketエラー\n");
		exit(1);
	}

	//ソケットの設定
	//IPアドレス(IPv4)
	addr.sin_family = AF_INET;

	//ポート番号	ウェルノウンポートと被らない番号
	addr.sin_port = htons(12345);

	//通信相手とするクライアントのアドレス制限
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//ソケットとローカル受付のポート番号の関連付けを行う
	//bindを行った後で初めて着信接続のlistenが可能になる
	//必要なのはサーバ側のソケットのみ
	//第一引数 : 作成したソケットへの参照
	//第二引数 : ソケットの接続情報
	//第三引数 : 接続情報のポインタの長さ
	//戻値 : エラーでない場合はゼロ
	//		 詳細なエラー内容を確認したい場合はWSAGetLastError関数で取得可
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		//エラー処理
		fprintf(stderr, "bindエラー\n");
		exit(1);
	}
	while (1)
	{
		//TCPクライアントからの接続要求を待てる状態にする
		//第一引数 : 作成したソケット
		//第二引数 : 保留中の接続バックログの最大の長さ
		//戻値 : エラーでない場合はゼロ
		//		 詳細なエラー内容を確認したい場合はWSAGetLastError関数で取得可
		if (listen(sock0, 5) < 0)
		{
			//エラー処理
			fprintf(stderr, "listenエラー\n");
			exit(1);
		}

	
		//TCPクライアントからの接続要求を受け付ける
		len = sizeof(client);

		//クライアント起動を要求
		printf("クライアントを起動してください\n");

		//ソケットのlistenを設定した後に保留中の接続要求を受け入れる
		//戻値として接続相手のソケット情報を返す
		//第一引数 : サーバ側のソケット情報
		//第二引数 : クライアントの接続情報(アドレス等)
		//第三引数 : クライアント接続情報を入れる構造体のポインタの長さ
		//			 現状ではオプション
		//			 処理に使用する機会がない
		//戻値 : 接続要求のあったクライアントのソケット情報
		//		 接続された相手との通信に使うソケットが入るので
		//		 サーバ側のソケット情報を保持している変数と
		//		 ひとつの構造体を共有することは不可
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0)
		{
			//エラー処理
			fprintf(stderr, "acceptエラー\n");
			exit(1);
		}

		//起動成功時
		printf("起動成功!\n");

		while (1)
		{
			//終了判断の変数
			int key;

			//送信するメッセージの変数
			char mes[256];

			//表示
			printf("送るメッセージを入力してください\n");

			//メッセージ入力
			scanf("%s", &mes);

			//メッセージサイズ取得
			mesSize = GET_ARRAY_SIZE(mes);

			//第一引数 : クライアント(送信先)のソケット情報
			//第二引数 : 送信したい情報の先頭アドレス
			//			 送信したいデータを格納しているバッファへのポインタ
			//戻値 : エラーでない場合は送信したバイト数
			//		 詳細なエラー内容を確認したい場合はWSAGetLastError関数で取得可
			if (send(sock, mes, mesSize, 0) < 0)
			{
				//エラー処理
				fprintf(stderr, "sendエラー\n");
				exit(1);
			}

			//送信完了時
			printf("送信完了!\n");
			printf("終了する場合はEscキーを押してください\n続行する場合はEsc以外のキーを入力してください\n");
			
			//Escキーが押されると終了する
			if ((key = getch()) == 0x1b)
			{
				exit(1);
			}
		}

		//TCPセッションの終了
		closesocket(sock);

		//入力処理
		buf = getchar();

		if (buf=='s')
		{
			break;
		}
	}

	//記述しなければメモリリークになってしまうため必須
	//winsock2の終了処理
	WSACleanup();

	//正常終了
	return 0;
}