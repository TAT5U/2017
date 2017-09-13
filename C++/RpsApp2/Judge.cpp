#include"Judge.h"
#include"Player.h"
#include<stdio.h>

//�v���C���[�̃C���X�^���X����
player player1("aaaaa"), player2("bbbbb");

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
void judge::Judgement(int pl1, int pl2)
{
	//�������ق��ɒʒB������
	if (pl1>pl2)
	{
		//�p�[ vs �`���L
		if (pl1 - pl2 >= 2)
		{
			printf("%s�̏���!\n",player2.getName().c_str());
			player2.notifyResult(true);
		}

		//�O�[ vs �`���Lor�p�[ vs �O�[
		else
		{
			printf("%s�̏���!\n",player1.getName().c_str());
			player1.notifyResult(true);
		}
	}
	else if (pl1<pl2)
	{
		//�`���L vs �p�[
		if (pl2 - pl1 >= 2)
		{
			printf("%s�̏���!\n", player1.getName().c_str());
			player1.notifyResult(true);
		}

		//�O�[ vs �p�[or�`���L vs �O�[
		else
		{
			printf("%s�̏���!\n",player2.getName().c_str());
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
	printf("%d��%d��", player1.getWinCount(), player2.getWinCount());
	if (player1.getWinCount()>player2.getWinCount())
	{
		printf("%s�̏���!\n", player1.getName().c_str());
	}
	else if (player1.getWinCount()<player2.getWinCount())
	{
		printf("%s�̏���!\n", player2.getName().c_str());
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
		p1 = player1.showHand();
		printf(" VS ");

		//�v���C���[2�̎���Ăяo��
		p2 = player2.showHand();

		//���s
		printf("\n");

		//�W�����P���̔���
		Judgement(p1, p2);

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