/*PlayScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"

#include "ClearScene.h"
/********************/


//�O���錾
class Tank;

//Scene�N���X���p������
class PlayScene : public Scene
{
	//�n��
	Fbx *ground;

	//���
	Tank *tank;

	//��(��Q��)
	Fbx *wall;

	//��(�A�C�e��)
	Fbx *star;

	//��
	Quad *tree;

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
	/****************************************************/
};