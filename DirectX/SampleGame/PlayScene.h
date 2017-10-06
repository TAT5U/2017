/*PlayScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
/********************/


//Scene�N���X���p������
class PlayScene : public Scene
{
	/****************�����蔻��****************/
	//�X�v���C�g�ƃ��x���œ����蔻����s������
	//�����o�ϐ����g�p����

	//�X�v���C�g
	Sprite *_sprite;

	//���x��
	Label *_label;
	/******************************************/

	//�X�v���C�g�̗L��
	bool _spriteFlg;

	//�|���S��
	Quad *_quad;

	//��]�p�x
	int _angle;

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
};