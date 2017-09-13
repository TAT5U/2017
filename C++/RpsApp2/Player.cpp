#include"Player.h"
#include<stdio.h>

//�������g�p���邽�߂̃w�b�_
#include<stdlib.h>
#include<time.h>

const int SCISSORS = 1;
const int STONE = 2;
const int PAPER = 3;

//�R���X�g���N�^	
player::player(string _name)
{
	name = _name;
	n = NULL;
	winCount = NULL;
}

//�f�X�g���N�^
player::~player()
{

}

//����o��
int player::showHand()
{
	//�[�������Ŏ擾
	n = GetRnd(SCISSORS, PAPER);

	if (n == SCISSORS)
	{
		printf("�`���L");
	}
	else if (n == STONE)
	{
		printf("�O�[");
	}
	else
	{
		printf("�p�[");
	}
	return n;
}

//�����̏������𓚂���
int player::getWinCount()
{
	return winCount;
}

//�������Ƃ��ɐR�����猋�ʂ����炤
void player::notifyResult(bool result)
{
	//�������J�E���g
	winCount++;
}

//�[�����������֐�
int player::GetRnd(int min, int max)
{
	static char flg;
	if (flg == 0)
	{
		srand((unsigned int)time(NULL));
		flg = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
string player::getName()
{
	return name;
}