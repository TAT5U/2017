/*2017-04-19
	��� �B��
		�s���~�b�h��\������v���O����*/

#include<stdio.h>
int main(void)
{
	//�i���A�J�E���g�̕ϐ�
	int StageNum = 0, i = 1, j = 1,k = 0;

	//�\��
	printf("�i�� : ");

	//�i������͂�����
	scanf("%d", &StageNum);

	//�󔒗p�̕ϐ��ɒi�����i�[
	k = StageNum;

	//�i�������[�v
	while (i<=StageNum)
	{

		//�K�v�ȋ󔒂����݂̒i������v�Z
		while (k-i>0)
		{
			//�\��
			printf("�@");

			//�}�C�i�X�J�E���g
			k--;
		}

		//*�̕\��
		while (j<=i*2-1)
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
		k = StageNum;

		//�J�E���g
		i++;
	}

	//����I��
	return 0;
}