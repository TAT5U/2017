/*Judge.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Node.h"
#include "Trump.h"
#include "Player.h"
/********************************/


class Judge
{
public:

	Judge();
	~Judge();

	//����
	bool Judgement(int *clickNumber);

	//���Ҕ���
	int GetWinner(Player **player);
};

