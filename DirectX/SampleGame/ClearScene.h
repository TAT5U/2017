/*ClearScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Scene.h"
/********************/


//Scene�N���X���p������
class ClearScene : public Scene
{
public:

	//�R���X�g���N�^
	ClearScene();

	//�f�X�g���N�^
	~ClearScene();

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