/*PlayScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
/********************/

enum  FrameState
{
	PLAYER = 1,
	CPU = -1,
	DEFAULT = 0,
};

enum  Judgement
{
	WIN = 1,
	LOSE = 2,
	Draw = 3,
};

//Scene�N���X���p������
class PlayScene : public Scene
{
	/****************�����蔻��****************/
	//�X�v���C�g�ƃ��x���œ����蔻����s������
	//�����o�ϐ����g�p����

	//�t���[��
	Sprite *frame[3][3];

	Sprite *circle, *cross;
	Sprite *gameMes;
	Sprite *frameBackGround;
	Sprite *frameMes;
	Sprite *retry, *end;
	Sprite *backGround;

	FrameState frameSt[3][3];

	bool turnFlg;
	bool gamePlayFlg;
	bool mesFlg;

	int x, y, playCount;

	float waitTime;

public:

	//�R���X�g���N�^
	PlayScene();

	//�f�X�g���N�^
	~PlayScene();

	/********************�������z�֐�********************/
	//�������z�֐��𕡐��g�p����̂ŃI�[�o�[���[�h����
	//�I�[�o�[���[�h���Ȃ��ꍇ�A�G���[��f��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Init() override;
	void Update() override;
	void Input() override;
	/****************************************************/

	Judgement GetJudge();
	void SimpleAI(int i);
};