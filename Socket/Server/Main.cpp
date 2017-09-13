/*2017-06-13
	��� �B��
		�T�[�o�T���v���v���O����*/

/*****�C���N���[�h*****/
#include<stdio.h>
#include<winsock2.h>
#include<conio.h>
/**********************/

/**************�����J**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/


#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

int main(void)
{
	//�ϐ���錾
	char buf;
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int mesSize;
	SOCKET sock;

	//�N����
	printf("�T�[�o�N�����E�E�E\n");

	//winsock2(Windows Sockket�̗�)�̏�����
	//winsock�𗘗p���邽�߂ɕK�v�ȏ������֐�
	//winsock�̗��p���͕K���Ăяo���K�v������
	//�v���O�����̐擪�ň�x�����s��
	//������ : �g�p����Windows�\�P�b�g�̃o�[�W�������
	//			 MAKEWORD()��2�̐��l����������
	//			 2�o�C�g�̃f�[�^���쐬����(0x0200�Ɠ���)
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
	//�\�P�b�g��1�ȏ�̃N���C�A���g�Ƒ΂ŏ��߂ĒʐM�\
	//�����Ŏg����ʐM�v���g�R���ɂ��Ă͉��L�Őݒ�
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
	//bind���s������ŏ��߂Ē��M�ڑ���listen���\�ɂȂ�
	//�K�v�Ȃ̂̓T�[�o���̃\�P�b�g�̂�
	//������ : �쐬�����\�P�b�g�ւ̎Q��
	//������ : �\�P�b�g�̐ڑ����
	//��O���� : �ڑ����̃|�C���^�̒���
	//�ߒl : �G���[�łȂ��ꍇ�̓[��
	//		 �ڍׂȃG���[���e���m�F�������ꍇ��WSAGetLastError�֐��Ŏ擾��
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		//�G���[����
		fprintf(stderr, "bind�G���[\n");
		exit(1);
	}
	while (1)
	{
		//TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
		//������ : �쐬�����\�P�b�g
		//������ : �ۗ����̐ڑ��o�b�N���O�̍ő�̒���
		//�ߒl : �G���[�łȂ��ꍇ�̓[��
		//		 �ڍׂȃG���[���e���m�F�������ꍇ��WSAGetLastError�֐��Ŏ擾��
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
		//�ߒl�Ƃ��Đڑ�����̃\�P�b�g����Ԃ�
		//������ : �T�[�o���̃\�P�b�g���
		//������ : �N���C�A���g�̐ڑ����(�A�h���X��)
		//��O���� : �N���C�A���g�ڑ���������\���̂̃|�C���^�̒���
		//			 ����ł̓I�v�V����
		//			 �����Ɏg�p����@��Ȃ�
		//�ߒl : �ڑ��v���̂������N���C�A���g�̃\�P�b�g���
		//		 �ڑ����ꂽ����Ƃ̒ʐM�Ɏg���\�P�b�g������̂�
		//		 �T�[�o���̃\�P�b�g����ێ����Ă���ϐ���
		//		 �ЂƂ̍\���̂����L���邱�Ƃ͕s��
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0)
		{
			//�G���[����
			fprintf(stderr, "accept�G���[\n");
			exit(1);
		}

		//�N��������
		printf("�N������!\n");

		while (1)
		{
			//�I�����f�̕ϐ�
			int key;

			//���M���郁�b�Z�[�W�̕ϐ�
			char mes[256];

			//�\��
			printf("���郁�b�Z�[�W����͂��Ă�������\n");

			//���b�Z�[�W����
			scanf("%s", &mes);

			//���b�Z�[�W�T�C�Y�擾
			mesSize = GET_ARRAY_SIZE(mes);

			//������ : �N���C�A���g(���M��)�̃\�P�b�g���
			//������ : ���M���������̐擪�A�h���X
			//			 ���M�������f�[�^���i�[���Ă���o�b�t�@�ւ̃|�C���^
			//�ߒl : �G���[�łȂ��ꍇ�͑��M�����o�C�g��
			//		 �ڍׂȃG���[���e���m�F�������ꍇ��WSAGetLastError�֐��Ŏ擾��
			if (send(sock, mes, mesSize, 0) < 0)
			{
				//�G���[����
				fprintf(stderr, "send�G���[\n");
				exit(1);
			}

			//���M������
			printf("���M����!\n");
			printf("�I������ꍇ��Esc�L�[�������Ă�������\n���s����ꍇ��Esc�ȊO�̃L�[����͂��Ă�������\n");
			
			//Esc�L�[���������ƏI������
			if ((key = getch()) == 0x1b)
			{
				exit(1);
			}
		}

		//TCP�Z�b�V�����̏I��
		closesocket(sock);

		//���͏���
		buf = getchar();

		if (buf=='s')
		{
			break;
		}
	}

	//�L�q���Ȃ���΃��������[�N�ɂȂ��Ă��܂����ߕK�{
	//winsock2�̏I������
	WSACleanup();

	//����I��
	return 0;
}