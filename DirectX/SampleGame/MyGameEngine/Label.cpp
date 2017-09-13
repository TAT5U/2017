/*Label.cpp*/

/*2017-07-13
	��� �B��
		���x����\�����邽�߂�
			�g�p����Label�v���O����*/

/****�C���N���[�h****/
#include "Label.h"
/********************/


//�R���X�g���N�^
Label::Label()
{
	//�ϐ��̏�����
	_pFont = nullptr;
	ZeroMemory(_string, sizeof(_string));
}

//�f�X�g���N�^
Label::~Label()
{
	//�J������
	_pFont->Release();
}

//�ÓI�֐�	���x���̍쐬��cocos2dx�̂悤�ȋL�q���ł���悤�ɂ���
Label *Label::Create(LPCSTR str, LPCSTR font, int size)
{
	Label *plabel = new Label();
	plabel->Load(font, size);
	plabel->SetString(str);
	return plabel;
}

//�t�H���g�̏���
void Label::Load(LPCSTR fontType, int fontSize)
{
	//2�Ԗڂ��t�H���g�T�C�Y
	//�Ōォ��2�Ԗڂ��t�H���g�̎��
	D3DXCreateFont(g.pDevice, fontSize, 0, FW_NORMAL, 1,
		FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, fontType, &_pFont);
}

//�����̕`��
void Label::Draw()
{
	//�`��ʒu(�͈�)�̐ݒ�
	//���E��E���E�����̏���
	RECT rect;
	rect.left = _position.x - _size.x * _anchorPoint.x * _scale.x;
	rect.top = _position.y - _size.y * _anchorPoint.y * _scale.y;
	rect.right = rect.left + _size.x * _scale.x;
	rect.bottom = rect.top + _size.y * _scale.y;

	//�����̊i�[
	//2�Ԗڂ��\�����镶����
	_pFont->DrawText(NULL, _string, -1, &rect,
		DT_LEFT | DT_TOP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

//�\�����镶���̕ύX
void Label::SetString(LPCSTR str)
{
	//��x�����o�ϐ��ɃR�s�[���Ă��當����ύX����
	strcpy(_string, str);
	RECT rect = { 0, 0, 0, 0 };
	_pFont->DrawText(NULL, _string, -1, &rect, DT_CALCRECT, NULL);
	_size.x = rect.right;
	_size.y = rect.bottom;
}