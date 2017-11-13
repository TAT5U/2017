/*Sprite.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include"Global.h"
#include "Node.h"
/********************/


//�摜��\�����邽�߂̃X�v���C�g�N���X
//Node�N���X���p��
class Sprite : public Node
{
	//�摜�̕\���̎d�g�݂̓e�N�X�`���ɉ摜���i�[���A�i�[�����e�N�X�`����
	//�X�v���C�g�ɓ\��t���ĕ`�悷��

	//�X�v���C�g
	LPD3DXSPRITE _pSprite;

	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 _pTexture, prevTexture;

	//�摜�̈ꕔ��؂�o��
	//�ؔ����͈�
	MyRect _cut;

	RECT cut;

	D3DXVECTOR3 anchor;

	int alpha;

public:

	//�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
	~Sprite();

	//�ÓI�֐�	�摜�̍쐬��cocos2dx�̂悤�ȋL�q���ł���悤�ɂ���
	//����->�摜���EMyRect�̍��W
	//�ߒl->�`�悷��Sprite
	static Sprite* Create(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));

	//�ǂݍ��ݏ���	�L�蓾�Ȃ��������i�[���Ƃ��Đؔ��������̗L�����m�F����
	//����->�摜���EMyRect�̍��W
	//�ߒl->�Ȃ�
	void Load(LPCSTR fileName,MyRect cut = MyRect(-999, -999, -999, -999));

	//�`�揈��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();

	/**********************�Z�b�^�[**********************/
	//�f�t�H���g�̒l���i�[���邱�Ƃɂ����
	//�l�����鎞�ɏȗ��ł���
	//�ؔ����͈͂��Z�b�g
	//����->MyRect�͈̔�
	//�ߒl->�Ȃ�
	void SetRect(MyRect cut);
	/****************************************************/

	void SetFadeValue(int val);
};