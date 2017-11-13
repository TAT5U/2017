/*Trump.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Sprite.h"
#include<time.h>
/********************************/


class Trump : public Sprite
{

	//�萔�錾
	static const int TRUMP_WIDTH = 100;
	static const int TRUMP_HEIGHT = 150;
	static const int TRUMP_MAX = 52;

	//�N���b�N���̃t���O
	static bool turnFlg[52];

public:

	Trump();
	~Trump();

	//�g�����v�z�u
	static Trump **Create();

	//�g�����v�̕��z�u
	static Trump **HandleCreate();

	//�V���b�t��
	void Shuffle(Trump **trump);

	//�N���b�N���̃t���O�ύX�Z�b�^�[
	void SetTurnFlag(bool val, int trumpCount);

	//�t���O�̃Q�b�^�[
	bool GetTurnFlag(int trumpCount);

	//�g�����v����
	static void RemoveTrump(Trump **trump, int *clickNumber);

};
