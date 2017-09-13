/*2017-06-13
	��� �B��
		�T�[�o�T���v���v���O����*/

/*****�C���N���[�h*****/
#include<stdio.h>
#include<winsock2.h>
#include<conio.h>
#include<iostream>
#include<cctype>
#include<time.h>
/**********************/

/**************�����J**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/
#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

int frame[3][3] = { 0 };
SOCKET sock;

// �\��
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

// ���s����
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
	//�ϐ���錾
	char key;
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int mesSize, mesSize2, mesMax;

	int x = 0, y = 0;
	int playCount = 0;

	char sendmes[256] = { 0 };

	//�N����
	printf("�T�[�o�N�����E�E�E\n");

	//winsock2(Windows Sockket�̗�)�̏�����
	int status = WSAStartup(MAKEWORD(2, 0), &wsaData);

	//�G���[����
	if (status != 0)
	{
		//�d���őg�ނȂ�l������K�v������
		switch (status)
		{
			//��������Ă��Ȃ�
		case WSASYSNOTREADY:
			break;

			//�o�[�W�������Ⴄ
		case WSAVERNOTSUPPORTED:
			break;

			//�ʐM���u���b�N����Ă���
		case WSAEINPROGRESS:
			break;

			//���d�N������Ă���
		case WSAEPROCLIM:
			break;
		}
	}

	//�\�P�b�g�̍쐬
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET)
	{
		//�G���[����
		fprintf(stderr, "socket�G���[\n");
		exit(1);
	}

	//�\�P�b�g�̐ݒ�
	//IP�A�h���X(IPv4)
	addr.sin_family = AF_INET;

	//�|�[�g�ԍ�	�E�F���m�E���|�[�g�Ɣ��Ȃ��ԍ�
	addr.sin_port = htons(12345);

	//�ʐM����Ƃ���N���C�A���g�̃A�h���X����
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//�\�P�b�g�ƃ��[�J����t�̃|�[�g�ԍ��̊֘A�t�����s��
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		//�G���[����
		fprintf(stderr, "bind�G���[\n");
		exit(1);
	}
	while (1)
	{
		//TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
		if (listen(sock0, 5) < 0)
		{
			//�G���[����
			fprintf(stderr, "listen�G���[\n");
			exit(1);
		}


		//TCP�N���C�A���g����̐ڑ��v�����󂯕t����
		len = sizeof(client);

		//�N���C�A���g�N����v��
		printf("�N���C�A���g���N�����Ă�������\n");

		//�\�P�b�g��listen��ݒ肵����ɕۗ����̐ڑ��v�����󂯓����
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0)
		{
			//�G���[����
			fprintf(stderr, "accept�G���[\n");
			exit(1);
		}

		//�N��������
		printf("�N������!\n");

		//�\��
		printf("�`�`�`�O�ڕ��ׁ`�`�`\n\n");

		while (1)
		{
			int judge;
			char recvbuf[256];

			//�I�����f�̕ϐ�
			int inputX = 0, inputY = 0;

			//���M���郁�b�Z�[�W�̕ϐ�
			char mes[256] = { 0 }, mes2[256] = { 0 };

			// �\��(����)
			printf("X���W\n");
			scanf("%s", &mes);
			printf("Y���W\n");
			scanf("%s", &mes2);
			inputX = *mes - '0';
			inputY = *mes2 - '0';
			while ((inputX > 2 || inputY > 2) || (frame[inputX][inputY] != 0))
			{
				printf("���W���s���ł�!!\n");
				printf("X���W\n");
				scanf("%s", &mes);
				printf("Y���W\n");
				scanf("%s", &mes2);
				inputX = *mes - '0';
				inputY = *mes2 - '0';
			}

			// ���W���i�[
			frame[inputX][inputY] = 1;
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

			// �\��
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

			// �Q�[�����J�E���g
			playCount++;

			// ���s����
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

			//�T�[�o����f�[�^����M
			memset(&recvbuf, 0, 256);

			//���b�Z�[�W�󂯎��
			int n = recv(sock, recvbuf, sizeof(recvbuf), 0);
			if (n < 0)
			{
				//�G���[����
				fprintf(stderr, "recv�G���[\n");
				exit(1);
			}

			// �ϊ����Ċi�[
			inputX = *(strtok(recvbuf, ",")) - '0';
			inputY = *(strtok(NULL, ",")) - '0';
			frame[inputX][inputY] = -1;

			// �\��
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

			// �Q�[�����J�E���g
			playCount++;

			// ���s����
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
	}

	//TCP�Z�b�V�����̏I��
	closesocket(sock);

	//�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	//winsock2�̏I������
	WSACleanup();

	//����I��
	return 0;
}

