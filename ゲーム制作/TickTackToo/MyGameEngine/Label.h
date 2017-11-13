/*Label.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Node.h"
/********************/


//������\�����邽�߂̃��x���N���X
//Node�N���X���p��
class Label : public Node
{
	//���x���̃t�H���g���i�[����ϐ�
	LPD3DXFONT _pFont;

	//�\�����镶�����i�[����ϐ�
	TCHAR _string[256];

public:

	//�R���X�g���N�^
	Label();

	//�f�X�g���N�^
	~Label();

	//�ÓI�֐�	���x���̍쐬��cocos2dx�̂悤�ȋL�q���ł���悤�ɂ���
	//����->�\�����镶���E�t�H���g�̎�ށE�t�H���g�T�C�Y
	//�ߒl->���x��
	static Label *Create(LPCSTR str, LPCSTR font, int size);

	//�t�H���g�̏���
	//����->�t�H���g�̎�ށE�t�H���g�T�C�Y
	//�ߒl->�Ȃ�
	void Load(LPCSTR fontType, int fontSize);

	//�����̕`��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();

	//�\�����镶���̕ύX
	//����->�\�����镶��
	//�ߒl->�Ȃ�
	void SetString(LPCSTR str);
};