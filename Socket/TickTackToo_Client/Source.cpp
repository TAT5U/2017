/*2017-06-13
��� �B��
�N���C�A���g�T���v���v���O����*/

/*****�C���N���[�h*****/
#include<stdio.h>
#include<winsock2.h>
#include<string>
#include<time.h>
/**********************/

/**************�����J**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/

#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))


int frame[3][3] = { 0 };

void DispTickTack(int i, int j)
{
	if (frame[i][j] == 0)
	{
		printf("|�@");
	}
	else if (frame[i][j] == 1)
	{
		printf("|��");
	}
	else if (frame[i][j] == -1)
	{
		printf("|�~");
	}


	if (i >= 2)
	{
		printf("|\n");
	}
}

int Judge()
{
	// ��
	if ((frame[0][0] + frame[1][0] + frame[2][0] == 3) || (frame[0][1] + frame[1][1] + frame[2][1] == 3) || (frame[0][2] + frame[1][2] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[1][0] + frame[2][0] == -3) || (frame[0][1] + frame[1][1] + frame[2][1] == -3) || (frame[0][2] + frame[1][2] + frame[2][2] == -3))
	{
		return -1;
	}

	// �c
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == 3) || (frame[1][0] + frame[1][1] + frame[1][2] == 3) || (frame[2][0] + frame[2][1] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == -3) || (frame[1][0] + frame[1][1] + frame[1][2] == -3) || (frame[2][0] + frame[2][1] + frame[2][2] == -3))
	{
		return -1;
	}

	// �΂�
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

	//�ϐ��錾
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;

	int x = 0, y = 0;
	int mesSize, mesSize2, mesMax;
	int playCount = 0;

	//�N����
	printf("�N���C�A���g�N�����E�E�E\n");

	//winsock2(Windows Sockket�̗�)�̏�����
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	//�\�P�b�g�̍쐬
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//�G���[����
		fprintf(stderr, "socket�G���[\n");
		exit(1);
	}

	//�ڑ���w��p�\���̂̏���
	server.sin_family = AF_INET;

	//�|�[�g�ԍ�	
	server.sin_port = htons(12345);

	//�ʐM����̃T�[�o��IP���X���i�[
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//�T�[�o�ɐڑ�
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		//�G���[����
		fprintf(stderr, "connect�G���[\n");
		exit(1);
	}

	//�N��������
	printf("�N������!\n");
	printf("�`�`�`�O�ڕ��ׁ`�`�`\n\n");

	while (1)
	{
		int judge;
		char buf[256];
		int inputX = 0, inputY = 0;

		//���M���郁�b�Z�[�W�̕ϐ�
		char mes[256], mes2[256], sendmes[256];
		int p;
		int q;

		//�T�[�o����f�[�^����M
		memset(&buf, 0, 256);

		//���b�Z�[�W�󂯎��
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n < 0)
		{
			//�G���[����
			fprintf(stderr, "recv�G���[\n");
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
			printf("����!\n");
			exit(1);
		}
		else if (judge == -1)
		{
			printf("����!\n");
			exit(1);
		}
		if (playCount >= 9)
		{
			printf("��������!\n");
			exit(1);
		}
		

		printf("X���W\n");
		scanf("%s", &mes);
		printf("Y���W\n");
		scanf("%s", &mes2);

		inputX = *mes - '0';
		inputY = *mes2 - '0';

		while (inputX > 2 || inputY > 2 || frame[inputX][inputY] != 0)
		{
			printf("���W���s���ł�!!\n");
			printf("X���W\n");
			scanf("%s", &mes);
			printf("Y���W\n");
			scanf("%s", &mes2);

			inputX = *mes - '0';
			inputY = *mes2 - '0';
		}
		frame[inputX][inputY] = -1;
		strcpy(sendmes, mes);
		strcat(sendmes, ",");
		strcat(sendmes, mes2);

		// ����
		if (send(sock, sendmes, strlen(sendmes), 0) < 0)
		{
			//�G���[����
			fprintf(stderr, "send�G���[\n");
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
			printf("����!\n");
			exit(1);
		}
		else if (judge == -1)
		{
			printf("����!\n");
			exit(1);
		}
		if (playCount >= 9)
		{
			printf("��������!\n");
			exit(1);
		}

	}

	//TCP�Z�b�V�����̏I��
	closesocket(sock);

	//�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	//winsock2�̏I������
	WSACleanup();

	//����I��
	return 0;
}