#include"Judge.h"
#include"Player.h"
#include<stdio.h>

//�v���C���[�̃C���X�^���X����
player player1, player2;

//�R���X�g���N�^
judge::judge()
{
	i = NULL;
	p1 = NULL;
	p2 = NULL;
}

//�f�X�g���N�^
judge::~judge()
{

}

//�W�����P���̔���
void judge::Judgement(int pl1,int pl2)
{
	//�������ق��ɒʒB������
	if (pl1>pl2)
	{
		//�p�[ vs �`���L
		if (pl1 - pl2 >= 2)
		{
			printf("�v���C���[2�̏���!\n");
			player2.notifyResult(true);
		}

		//�O�[ vs �`���Lor�p�[ vs �O�[
		else
		{
			printf("�v���C���[1�̏���!\n");
			player1.notifyResult(true);
		}
	}
	else if (pl1<pl2)
	{
		//�`���L vs �p�[
		if (pl2 - pl1 >= 2)
		{
			printf("�v���C���[1�̏���!\n");
			player1.notifyResult(true);
		}

		//�O�[ vs �p�[or�`���L vs �O�[
		else
		{
			printf("�v���C���[2�̏���!\n");
			player2.notifyResult(true);
		}
	}
	//��������
	else
	{
		printf("��������!\n");
	}
}

//�ŏI���ʂ̔���
void judge::WinnerJudge()
{
	printf("%d��%d��", player1.getWinCount(),player2.getWinCount());
	if (player1.getWinCount()>player2.getWinCount())
	{
		printf("�v���C���[1�̏���!\n");
	}
	else if (player1.getWinCount()<player2.getWinCount())
	{
		printf("�v���C���[2�̏���!\n");
	}
	else
	{
		printf("��������!\n");
	}
}

//�Q�[���i�s
void judge::Disp()
{
	printf("����񂯂�X�^�[�g!\n");
	while (i < 3)
	{
		printf("[%d���]\n", i + 1);

		//�v���C���[1�̎���Ăяo��
		p1=player1.showHand();
		printf(" VS ");

		//�v���C���[2�̎���Ăяo��
		p2=player2.showHand();

		//���s
		printf("\n");

		//�W�����P���̔���
		Judgement(p1,p2);

		//���s
		printf("\n");

		//�������J�E���g
		i++;
	}
	//���s
	printf("\n");

	//�ŏI���ʂ̔���
	WinnerJudge();
}