/*Score.h*/

#include<stdio.h>
#include<stdlib.h>
class Score
{
public:

	//�t�@�C���|�C���^
	FILE *fp;

	//�X�R�A�E�����N�p�ϐ�
	int score =0 ,*rank = 0,Rank = 0,cnt = 0,i = 0;

	//work�E�t���O�p�ϐ�
	int work = 0, sortFlg = 0, k = 0;

	//�X�R�A��������
	int SetScore(int x);

	//�X�R�A�ǂݏo��
	int GetScore(int flg,int i2);

	//�X�R�A�\�[�g
	void Sort();
};

