/*Score.cpp*/

/*2017-06-01
	TAT5U
		�X�R�A��������*/

#include "Score.h"

//�X�R�A��������
int Score::SetScore(int x)
{
	//score.dat���J���E�Ȃ���΍쐬
	fp = fopen("data/score.dat", "ab");

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
int Score::GetScore(int flg)
{
	int score = 999, work = 0;
	//score.dat���J��
	fp = fopen("data/score.dat", "rb");

	//�G���[��NULL��Ԃ�
	if (fp == NULL)
	{
		return NULL;
	}
	//�Ō�܂œǂݍ���
	while (fread(&work, sizeof(work), 1, fp))
	{
		//1�ԑ��������X�R�A��score�Ɋi�[
		if (score>work&&work != 0)
		{
			score = work;
		}
	}
	//����
	fclose(fp);

	//�n�C�X�R�A��Ԃ�
	if (flg==0)
	{
		return score;
	}

	//�����̃X�R�A��Ԃ�
	else if (flg==1)
	{
		return work;
	}
}
