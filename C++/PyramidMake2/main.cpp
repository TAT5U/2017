/*2017-04-19
��� �B��
	�s���~�b�h��\������v���O����
				���L�[�ŉ�]������*/

#include<stdio.h>

//system�R�}���h���g�p���邽�߂̃w�b�_
#include <stdlib.h>

//getch���g�p���邽�߂̃w�b�_
#include<conio.h>

int main(void)
{
	//�i���A�J�E���g�̕ϐ�
	int StageNum = 0, i = 1, j = 1, k = 0, key = 0, HNum = 0, cnt = 0;

	//�L�[�������ꂽ�Ƃ��̃t���O
	bool flgU = false, flgD = false, flgR = false, flgL = false;

	//�\��
	printf("�i�� : ");

	//�i������͂�����
	scanf("%d", &StageNum);

	//�󔒗p�̕ϐ��ɒi�����i�[
	k = StageNum;

	//�i�������[�v
	while (i <= StageNum)
	{
		//�K�v�ȋ󔒂����݂̒i������v�Z
		while (k - i>0)
		{
			//�󔒕\��
			printf("�@");

			//�󔒗p�̕ϐ��}�C�i�X�J�E���g
			k--;
		}

		//*�̕\��
		while (j <= i * 2 - 1)
		{
			//�\��
			printf("��");

			//�Ō�̒i�̐����J�E���g
			if (i==StageNum)
			{
				cnt++;
			}
			//�J�E���g
			j++;
		}

		//���s
		printf("\n");

		//���ꂼ��̕ϐ��������l�ɖ߂�
		j = 1;
		k = StageNum;

		//�J�E���g
		i++;
	}

	//�L�[����(���)�ŉ�]&Esc�ŏI��
	while (1)
	{
		//�L�[����
		key = getch();

		//���L�[�͓����2�o�C�g�̃R�[�h�ɂȂ�
		//��󂩂ǂ����̊m�F
		if (key==0xe0)
		{
			//������x�i�[
			key = getch();

			//���������ꂽ�Ƃ��͉E�ɉ�]�����s���~�b�h�\��
			if (key == 0x4d)
			{
				//���������ꑱ���Ă��Ȃ����
				if (flgR==false)
				{
					//�\����1�x����
					system("cls");

					//�\��
					printf("�i�� : %d\n", StageNum);

					//�t���O�̕ύX
					flgR = true;
					flgD = false;
					flgL = false;
					flgU = false;

					//�i���̕ϐ��������l�ɖ߂�
					i = 1, j = 1;

					//��]�����s���~�b�h�̏㔼���̒i�����i�[
					HNum = cnt / 2;

					//�㔼���̃��[�v
					while (i <= HNum + 1)
					{
						//*�̕\��
						while (j <= i)
						{
							//�\��
							printf("��");

							//�J�E���g
							j++;
						}

						//���s
						printf("\n");

						//�ϐ��������l�ɖ߂�
						j = 1;

						//�J�E���g
						i++;
					}

					//�������̒i�����i�[&�����l�ɖ߂�
					i = HNum;
					j = 1;

					//�������̃��[�v
					while (i > 0)
					{
						//*�̕\��
						while (j <= i)
						{
							//�\��
							printf("��");

							//�J�E���g
							j++;
						}

						//���s
						printf("\n");

						//�ϐ��������l�ɖ߂�
						j = 1;

						//�}�C�i�X�J�E���g
						i--;
					}
				}

			}

			//���������ꂽ�Ƃ��͉��ɉ�]�����s���~�b�h�\��
			else if (key == 0x50)
			{
				//���������ꑱ���Ă��Ȃ����
				if (flgD==false)
				{
					//�\����1�x����
					system("cls");

					//�\��
					printf("�i�� : %d\n", StageNum);

					//�t���O�̕ύX
					flgR = false;
					flgD = true;
					flgL = false;
					flgU = false;

					//�i���A�J�E���g�̕ϐ�
					i = 0, j = 0, k = 1;

					//�i�������[�v
					while (i <= StageNum)
					{
						//�󔒂̕\��
						while (k <= i)
						{
							//�󔒕\��
							printf("�@");

							//�󔒗p�̕ϐ��J�E���g
							k++;
						}

						//*�̕\��
						while (j <= StageNum * 2 - i * 2 - 2)
						{
							//�\��
							printf("��");

							//�J�E���g
							j++;
						}

						//���s
						printf("\n");

						//���ꂼ��̕ϐ��������l�ɖ߂�
						j = 0;
						k = 1;

						//�J�E���g
						i++;
					}
				}
				
			}

			//���������ꂽ�Ƃ��͍��ɉ�]�����s���~�b�h�\��
			else if (key == 0x4b)
			{
				//���������ꑱ���Ă��Ȃ����
				if (flgL==false)
				{
					//�\����1�x����
					system("cls");

					//�\��
					printf("�i�� : %d\n", StageNum);

					//�t���O�̕ύX
					flgR = false;
					flgD = false;
					flgL = true;
					flgU = false;

					//�i���A�J�E���g�̕ϐ�
					i = 1, j = 1, k = 0;

					//��]�����s���~�b�h�̏㔼���̒i�����i�[
					HNum = cnt / 2;

					//�㔼���̃��[�v
					while (i <= HNum + 1)
					{
						//�󔒂̕\��
						while (k <= HNum - i)
						{
							//�󔒕\��
							printf("�@");

							//�󔒗p�̕ϐ��J�E���g
							k++;
						}

						//*�̕\��
						while (j <= i)
						{
							//�\��
							printf("��");

							//�J�E���g
							j++;
						}

						//���s
						printf("\n");

						//���ꂼ��̕ϐ��������l�ɖ߂�
						j = 1;
						k = 0;

						//�J�E���g
						i++;
					}

					//���ꂼ��̕ϐ��������l�ɖ߂�
					i = 1;
					j = 1;
					k = 0;

					//�������̃��[�v
					while (i <= HNum)
					{
						//�󔒂̕\��
						while (k <= i - 1)
						{
							//�󔒕\��
							printf("�@");

							//�󔒗p�̕ϐ��J�E���g
							k++;
						}
						//*�̕\��
						while (j <= HNum - i + 1)
						{
							//�\��
							printf("��");

							//�J�E���g
							j++;
						}

						//���s
						printf("\n");

						//���ꂼ��̕ϐ��������l�ɖ߂�
						k = 0;
						j = 1;

						//�J�E���g
						i++;
					}
				}
				
			}

			//���������ꂽ�Ƃ��͌��̌����̃s���~�b�h�\��
			else if (key == 0x48)
			{
				//���������ꑱ���Ă��Ȃ����
				if (flgU==false)
				{
					//�\����1�x����
					system("cls");

					//�\��
					printf("�i�� : %d\n", StageNum);

					//�t���O�̕ύX
					flgR = false;
					flgD = false;
					flgL = false;
					flgU = true;

					//�i���A�J�E���g�̕ϐ�
					i = 1, j = 1, cnt = 0;

					//�󔒗p�̕ϐ��ɒi�����i�[
					k = StageNum;

					//�i�������[�v
					while (i <= StageNum)
					{
						//�K�v�ȋ󔒂����݂̒i������v�Z
						while (k - i>0)
						{
							//�\��
							printf("�@");

							//�}�C�i�X�J�E���g
							k--;
						}

						//*�̕\��
						while (j <= i * 2 - 1)
						{
							//�\��
							printf("��");
							if (i == StageNum)
							{
								cnt++;
							}
							//�J�E���g
							j++;
						}
						//���s
						printf("\n");

						//���ꂼ��̕ϐ��������l�ɖ߂�
						j = 1;
						k = StageNum;

						//�J�E���g
						i++;
					}
				}
				
			}
		}
		//Esc�����͂��ꂽ��I��
		else if (key == 27)
		{
			break;
		}
	}

	//����I��
	return 0;
}
