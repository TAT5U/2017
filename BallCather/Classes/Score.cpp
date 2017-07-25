#include "Score.h"

//�X�R�A��������
int Score::SetScore(int x)
{
	//score.dat���J���E�Ȃ���΍쐬
	fp = fopen("score.dat", "ab");

	//�G���[�ŏI��
	if (fp == NULL)
	{
		exit(1);
	}
	
	//��������
	fwrite(&x, sizeof(x), 1, fp);

	//����
	fclose(fp);
}
//�X�R�A�ǂݏo��
int Score::GetScore(int flg,int i2)
{
	//�ϐ�������
	cnt = 0;
	i = 0;

	//score.dat���J��
	fp = fopen("score.dat", "rb");

	//�G���[�ŏI��
	if (fp == NULL)
	{
		exit(1);
	}
	
	//�������܂�Ă���X�R�A�̑������J�E���g
	while (fread(&score, sizeof(score), 1, fp))
	{
		cnt++;
	}

	//����
	fclose(fp);

	//�����̃X�R�A�����ǂݏo��
	if (flg == 0)
	{
		return score;
	}

	//���I�z��쐬
	rank = new int[cnt];

	//score.dat���J
	fp = fopen("score.dat", "rb");

	//�G���[�ŏI��
	if (fp == NULL)
	{
		exit(1);
	}

	//�������܂�Ă���X�R�A��ǂݏo��
	while (fread(&rank[i], sizeof(rank[i]), 1, fp))
	{
		i++;
	}

	//�\�[�g�����s
	Sort();

	//����
	fclose(fp);

	//�����̏��ʂ����ǂݏo��
	if (flg==1)
	{
		i = 0;
		while (i<cnt)
		{
			//�����̏��ʂ�T��
			if (rank[i] == score)
			{
				delete[]rank;
				return i+1;
			}
			i++;
		}
	}

	//��ʂ̃X�R�A��ǂݏo��
	else if (flg==2)
	{
		//��������邽��
		Rank = rank[i2];
		delete[]rank;
		return Rank;
	}

	//10�ʈȏ�X�R�A�������ĂȂ����ǂ���
	else if (flg==3)
	{
		delete[]rank;
		return cnt;
	}
}
//�X�R�A�\�[�g
void Score::Sort()
{
	//�ϐ�������
	k = 0;
	i = 0;

	//�o�u���\�[�g�œ���ւ�
	do
	{
		sortFlg = 0;
		while (i < cnt - 1 - k)
		{
			if (rank[i] < rank[i + 1])
			{
				sortFlg = 1;
				work = rank[i];
				rank[i] = rank[i + 1];
				rank[i + 1] = work;
			}
			i++;
		}
		i = 0;
		k++;
	} while (sortFlg == 1);
}
