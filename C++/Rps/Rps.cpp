/*2017-05-12
	��� �B��
		�W�����P���v���O����*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Rps.h"

const int SCISSORS = 1;
const int STONE = 2;
const int PAPER = 3;

//�R���X�g���N�^
Rps::Rps()
{
	p1 = 0, p2 = 0;
}

//�[�����������֐�
int Rps::GetRnd(int min, int max)
{
	static char flg;
	if (flg==0)
	{
		srand((unsigned int)time(NULL));
		flg = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//�W�����P���̔���
int Rps::Judge(int n, int m)
{
	if (n>m)
	{
		//�p�[ vs �`���L
		if (n-m>=2)
		{
			p2++;
			Rps::p2Disp();
		}

		//�O�[ vs �`���Lor�p�[ vs �O�[
		else
		{
			p1++;
			Rps::p1Disp();
		}

	}
	else if (n<m)
	{
		//�`���L vs �p�[
		if (m-n>=2)
		{
			p1++;
			Rps::p1Disp();
		}

		//�O�[ vs �p�[or�`���L vs �O�[
		else
		{
			p2++;
			Rps::p2Disp();
		}
	}
	//��������
	else
	{
		Rps::p1p2Disp();
	}
	return 0;
}

//�W�����P���̕\��
int Rps::JudgeDisp(int n)
{
	if (n==SCISSORS)
	{
		printf("�`���L");
	}
	else if (n==STONE)
	{
		printf("�O�[");
	}
	else
	{
		printf("�p�[");
	}
	return 0;
}

//�v���C���[1�̏������̕\��
void Rps::p1Disp()
{
	printf("�v���C���[1�̏���!\n");
}

//�v���C���[2�̏������̕\��
void Rps::p2Disp()
{
	printf("�v���C���[2�̏���!\n");
}

//���������̍ۂɕ\��
void Rps::p1p2Disp()
{
	printf("��������!\n");
}

//3�񏟕��������ʂ�\��
void Rps::Disp()
{
	printf("%d��%d��",p1,p2);
	if (p1>p2)
	{
		Rps::p1Disp();
	}
	else if (p1<p2)
	{
		Rps::p2Disp();
	}
	else
	{
		Rps::p1p2Disp();
	}
}

//���C���֐�
int main(void)
{
	int i = 0, p1s = 0, p2s = 0;
	Rps rps;
	printf("����񂯂�X�^�[�g!\n");
	while (i<3)
	{
		printf("[%d���]\n", i + 1);

		//�v���C���[1�̎�I��
		p1s = rps.GetRnd(SCISSORS,PAPER);
		
		//��̕\��
		rps.JudgeDisp(p1s);
		printf(" VS ");

		//�v���C���[2�̎�I��
		p2s = rps.GetRnd(SCISSORS, PAPER);

		//��̕\��
		rps.JudgeDisp(p2s);

		//���s
		printf("\n");

		//�W�����P���̔���
		rps.Judge(p1s, p2s);

		//���s
		printf("\n");

		//�J�E���g
		i++;
	}

	//���ʕ\��
	rps.Disp();

	//����I��
	return 0;
}