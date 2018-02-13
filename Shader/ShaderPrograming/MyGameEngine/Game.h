/*Game.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Global.h"
#include "Sprite.h"
#include "Scene.h"
#include "Input.h"
#include "Fade.h"

//�V�[���̃w�b�_
#include "../Sample.h"
/********************/


//�Q�[�����������邽�߂̃N���X(�`��Ȃ�)
class Game
{
	//LP�́uLong�@Pointer�v�Ȃ̂Ń|�C���^�Ƃ��Ĉ���
	//Directx3D�I�u�W�F�N�g
	LPDIRECT3D9 _pD3d;

public:

	//�R���X�g���N�^
	Game();

	//�f�X�g���N�^
	~Game();

	//����������
	//Direct3D�f�o�C�X�I�u�W�F�N�g���g�p���邽�߂̈����ɃE�B���h�E�n���h����ݒ�
	//����->�E�B���h�E�n���h��
	//�ߒl->�Ȃ�
	HRESULT Init(HWND hWnd);

	//�X�V����
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Update();

	//���͏���
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Input();

	//�`�揈��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();
};