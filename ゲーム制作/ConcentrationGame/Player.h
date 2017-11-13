/*Player.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "Score.h"
/********************************/


class Player : public Score
{
	//�萔
	static const int PLAYER_MAX = 4;

	//�v���C���[��
	static TCHAR name[4][128];

public:

	Player();
	~Player();

	//�v���C���[�쐬
	static Player **Create();

	//�v���C���[�̖��O�ƃX�R�A��\��
	void PlayerScore(TCHAR *label, int count, Player *player);

	//�v���C���[�̃X�R�A���Z�b�g
	void SetPlayerScore(Player *player, int count);
};

