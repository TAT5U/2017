/*Score.cpp*/

#include "Score.h"

//static�Ȃ̂ŊO���Ő錾
int Score::score[4];

Score::Score()
{

}


Score::~Score()
{

}

//�Z�b�^�[
void Score::SetScore(int val, int count)
{
	score[count] += val;
}

//�Q�b�^�[
int Score::GetScore(int count)
{
	return score[count];
}

//�X�R�A�̏�����
void Score::InitializeScore(int count)
{
	score[count] = 0;
}