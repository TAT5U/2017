/*2017-06-13
狩野 達哉
クライアントサンプルプログラム*/

/*****インクルード*****/
#include<stdio.h>
#include<winsock2.h>
#include<string>
#include<time.h>
/**********************/

/**************リンカ**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/

#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))


int frame[3][3] = { 0 };

void DispTickTack(int i, int j)
{
	if (frame[i][j] == 0)
	{
		printf("|　");
	}
	else if (frame[i][j] == 1)
	{
		printf("|○");
	}
	else if (frame[i][j] == -1)
	{
		printf("|×");
	}


	if (i >= 2)
	{
		printf("|\n");
	}
}

int Judge()
{
	// 横
	if ((frame[0][0] + frame[1][0] + frame[2][0] == 3) || (frame[0][1] + frame[1][1] + frame[2][1] == 3) || (frame[0][2] + frame[1][2] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[1][0] + frame[2][0] == -3) || (frame[0][1] + frame[1][1] + frame[2][1] == -3) || (frame[0][2] + frame[1][2] + frame[2][2] == -3))
	{
		return -1;
	}

	// 縦
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == 3) || (frame[1][0] + frame[1][1] + frame[1][2] == 3) || (frame[2][0] + frame[2][1] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == -3) || (frame[1][0] + frame[1][1] + frame[1][2] == -3) || (frame[2][0] + frame[2][1] + frame[2][2] == -3))
	{
		return -1;
	}

	// 斜め
	// *   *
	//   *
	// *   *
	else if ((frame[0][0] + frame[1][1] + frame[2][2] == 3) || (frame[2][0] + frame[1][1] + frame[0][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[1][1] + frame[2][2] == -3) || (frame[2][0] + frame[1][1] + frame[0][2] == -3))
	{
		return -1;
	}

	return 0;
}

int main(void)
{
	char key;

	//変数宣言
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;

	int x = 0, y = 0;
	int mesSize, mesSize2, mesMax;
	int playCount = 0;

	//起動時
	printf("クライアント起動中・・・\n");

	//winsock2(Windows Sockketの略)の初期化
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	//ソケットの作成
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//エラー処理
		fprintf(stderr, "socketエラー\n");
		exit(1);
	}

	//接続先指定用構造体の準備
	server.sin_family = AF_INET;

	//ポート番号	
	server.sin_port = htons(12345);

	//通信相手のサーバのIP青レスを格納
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//サーバに接続
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		//エラー処理
		fprintf(stderr, "connectエラー\n");
		exit(1);
	}

	//起動成功時
	printf("起動成功!\n");
	printf("～～～三目並べ～～～\n\n");

	while (1)
	{
		int judge;
		char buf[256];
		int inputX = 0, inputY = 0;

		//送信するメッセージの変数
		char mes[256], mes2[256], sendmes[256];
		int p;
		int q;

		//サーバからデータを受信
		memset(&buf, 0, 256);

		//メッセージ受け取り
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n < 0)
		{
			//エラー処理
			fprintf(stderr, "recvエラー\n");
			exit(1);
		}
		inputX = *(strtok(buf, ","))-'0';
		inputY = *(strtok(NULL, ",")) - '0';
		frame[inputX][inputY] = 1;

		printf("      0  1  2  \n");
		while (y < 3)
		{
			printf("    -----------\n");
			printf(" %d  ", y);
			while (x < 3)
			{
				DispTickTack(x, y);
				x++;
			}
			x = 0;
			y++;
		}
		printf("    -----------\n");
		x = 0;
		y = 0;
		printf("\n");
		playCount++;

		judge = Judge();
		if (judge == 1)
		{
			printf("負け!\n");
			exit(1);
		}
		else if (judge == -1)
		{
			printf("勝ち!\n");
			exit(1);
		}
		if (playCount >= 9)
		{
			printf("引き分け!\n");
			exit(1);
		}
		

		printf("X座標\n");
		scanf("%s", &mes);
		printf("Y座標\n");
		scanf("%s", &mes2);

		inputX = *mes - '0';
		inputY = *mes2 - '0';

		while (inputX > 2 || inputY > 2 || frame[inputX][inputY] != 0)
		{
			printf("座標が不正です!!\n");
			printf("X座標\n");
			scanf("%s", &mes);
			printf("Y座標\n");
			scanf("%s", &mes2);

			inputX = *mes - '0';
			inputY = *mes2 - '0';
		}
		frame[inputX][inputY] = -1;
		strcpy(sendmes, mes);
		strcat(sendmes, ",");
		strcat(sendmes, mes2);

		// 送る
		if (send(sock, sendmes, strlen(sendmes), 0) < 0)
		{
			//エラー処理
			fprintf(stderr, "sendエラー\n");
			exit(1);
		}

		printf("      0  1  2  \n");
		while (y < 3)
		{
			printf("    -----------\n");
			printf(" %d  ", y);
			while (x < 3)
			{
				DispTickTack(x, y);
				x++;
			}
			x = 0;
			y++;
		}
		printf("    -----------\n");
		x = 0;
		y = 0;
		printf("\n");
		playCount++;
		judge = Judge();
		if (judge == 1)
		{
			printf("負け!\n");
			exit(1);
		}
		else if (judge == -1)
		{
			printf("勝ち!\n");
			exit(1);
		}
		if (playCount >= 9)
		{
			printf("引き分け!\n");
			exit(1);
		}

	}

	//TCPセッションの終了
	closesocket(sock);

	//記述しなければメモリリークになってしまうため必須
	//winsock2の終了処理
	WSACleanup();

	//正常終了
	return 0;
}