/*Score.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Label.h"
/********************************/


class Score : public Label
{
	//�v���C���[���Ƃ̃X�R�A
	static int score[4];

public:

	Score();
	~Score();

	//�X�R�A�̃Z�b�^�[�ƃQ�b�^�[
	void SetScore(int val, int count);
	int GetScore(int count);

	//�X�R�A�̏�����
	void InitializeScore(int count);
};