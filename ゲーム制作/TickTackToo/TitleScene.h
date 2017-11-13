/*TitleScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
#include "MyGameEngine\Fade.h"
#include "PlayScene.h"
/********************/


//Scene�N���X���p������
class TitleScene : public Scene
{
	Sprite *backGround;
	Sprite *title;
	Sprite *start;

	int alpha;
	bool fadeFlg;
	bool isFadeFlg;

public:

	//�R���X�g���N�^
	TitleScene();

	//�f�X�g���N�^
	~TitleScene();

	/********************�������z�֐�********************/
	//�������z�֐��𕡐��g�p����̂ŃI�[�o�[���[�h����
	//�I�[�o�[���[�h���Ȃ��ꍇ�A�G���[��f��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Init() override;
	void Update() override;
	void Input() override;
	/****************************************************/;
};