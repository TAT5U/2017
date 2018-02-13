/*Global.h*/

//�C���N���[�h�K�[�h
//��d�ɃC���N���[�h���邱�Ƃ�h���ł����
//#ifndef�Ɠ���
#pragma once

/***************�C���N���[�h***************/
//WindowsAPI���g�p�\�ɂ���
#include<windows.h>

//�����DirectX���g�p�ł���悤�ɂȂ�
//DirectX�̃w�b�_
#include<d3dx9.h>

//�����ɋL�q�łǂ��ł��g�p���邱�Ƃ��ł���
//�I���W�i����MyRect�w�b�_
#include "MyRect.h"

#include "Input.h"
/******************************************/


//delete����null���i�[���鐳������������̃}�N����
#define SAFE_DELETE(X) if(X){delete X; X = nullptr;}
#define SAFE_RELEASE(X) if(X){X->Release(); X = nullptr;}


//���݂��ɃC���N���[�h�������ƃG���[��f���Ă��܂�
//�Б������C���N���[�h�ł��G���[��f���Ă��܂�
//���̏ꍇ�ɂ̓w�b�_���C���N���[�h���Ȃ��őO���錾�Ƃ������̂��g�p����
//�O���錾�̓v���g�^�C�v�錾�̃N���X�o�[�W����
//�g�p���邱�Ƃɂ���āy�錾�����^�̃|�C���^�z�Ȃ�錾�ł���悤�ɂȂ�
//�O���錾
class Scene;
class Fade;


//WinMain�ƃv���V�[�W���̓N���X���~
//�ǂ��̃N���X�ł��g���萔��錾����O���[�o���N���X
class Global
{
	bool fadeFlg;

	bool endFlg;

public:

	Global();

	//�萔�錾
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	const float STANDARD_CONTENT_WIDTH;
	const float STANDARD_CONTENT_HEIGHT;

	//�����x��MAX�l�EMIN�l
	const int ALPHA_MAX, ALPHA_MIN;

	//Direct3D�f�o�C�X�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 pDevice;

	//�V�[�����Ǘ����邽�߂̕ϐ�
	Scene *pScene;

	//���̓f�o�C�X�̊Ǘ�
	Input *pInput;

	Fade *pFade;

	//�V�[���؂�ւ�
	//����->���̃V�[��
	//�ߒl->�Ȃ�
	void ReplaceScene(Scene *pNextScene);

	void SetAlphaFlg(bool flg);

	bool GetAlphaFlg();

	void SetEndFlg(bool flg);

	bool GetEndFlg();
};

//�����Ŏg�p����萔�Ȃǂ�������cpp�Ŏg����ꍇ�ȂǂɎg�p����
//���̕��@�Ƃ��ăV���O���g��������
//�O���[�o���I�u�W�F�N�g(�O���錾)
extern Global g;