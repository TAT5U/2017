/*2017-06-13
	��� �B��
		�N���C�A���g�T���v���v���O����*/

/*****�C���N���[�h*****/
#include<stdio.h>
#include<winsock2.h>
/**********************/

/**************�����J**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/

int main(void)
{
	//�ϐ��錾
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;
	char buf[256];

	//�N����
	printf("�N���C�A���g�N�����E�E�E\n");

	//winsock2(Windows Sockket�̗�)�̏�����
	//winsock�𗘗p���邽�߂ɕK�v�ȏ������֐�
	//winsock�̗��p���͕K���Ăяo���K�v������
	//�v���O�����̐擪�ň�x�����s��
	//������ : �g�p����Windows�\�P�b�g�̃o�[�W�������
	//			 MAKEWORD()��2�̐��l����������
	//			 2�o�C�g�̃f�[�^���쐬����(0x0200�Ɠ���)
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	//�\�P�b�g�̍쐬
	//������ : int�^�̃A�h���X�t�@�~��(OSI ��4�w�g�����X�|�[�g�w)
	//			 ��) AF_INET == IPv4�A�h���X���T�|�[�g����悤�ɐݒ�
	//������ : �쐬����\�P�b�g�̎��
	//			 TCP��UDP�Ƃ������ʐM��̎菇���w��
	//			 SOCK_STREAM��TCP���g�p���A�A�h���X�t�@�~����
	//			 IPv4(AF_INET)���AIPv6(AF_INET6)���g�p����
	//��O���� : �g�p����v���g�R�����L�q�A�[����TCP���w��
	//			 �Ȃ��A�h���X�t�@�~���͑������Ɠ�������
	//			 ���A��������SOCK_STREAM�ł���K�v������
	//�ߒl : �G���[�R�[�h(���s�����INVALID_COCKET��Ԃ�)
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		//�G���[����
		fprintf(stderr, "socket�G���[\n");
		exit(1);
	}

	//�ڑ���w��p�\���̂̏���
	//�T�[�o���̏��
	//IP�A�h���X(IPv4)
	server.sin_family = AF_INET;

	//�|�[�g�ԍ�	
	//������ : �|�[�g�ԍ� �E�F���m�E���|�[�g�Ɣ��Ȃ��ԍ�
	//�ߒl		 TCP/IP�l�b�g���[�N�ɂ��IP�A�h���X�Ɠ����K�i�ɕϊ������l
	server.sin_port = htons(12345);

	//�ʐM����̃T�[�o��IP���X���i�[
	//������ : �ʐM�����IP�A�h���X�́w.�x��t�������
	//�ߒl		 �G���[�R�[�h(���s�����INADDR_NONE��Ԃ�)
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//�T�[�o�ɐڑ�
	//������ : �쐬�����\�P�b�g
	//������ : �T�[�o�̐ڑ����
	//��O���� : �T�[�o�̃T�C�Y
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		//�G���[����
		fprintf(stderr, "connect�G���[\n");
		exit(1);
	}

	//�N��������
	printf("�N������!\n");

	while (1)
	{
		//�T�[�o����f�[�^����M
		//������ : �T�[�o����󂯎�����f�[�^���i�[����ϐ�
		//������ : 
		//��O���� : �󂯎�����f�[�^�̕�����(�o�C�g)
		memset(buf, 0, sizeof(buf));

		//���b�Z�[�W�󂯎��
		int n = recv(sock, buf, sizeof(buf), 0);
		if (n < 0)
		{
			//�G���[����
			fprintf(stderr, "recv�G���[\n");
			exit(1);
		}

		//�T�[�o����󂯎�����f�[�^�ƕ����񐔂�\������
		printf("%s\n",buf);
	}


	//�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	//winsock2�̏I������
	WSACleanup();

	//���͏���
	//�������͂�����I������
	//�T�[�o����󂯎�����l�������悤�ɂ��邽��
	getchar();

	//����I��
	return 0;
}