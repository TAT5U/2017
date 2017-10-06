/*MyRect.cpp*/

/*2017-06-07
	��� �B��
		cocos2dx�̂悤��Rect�̎g����
			�����邽�߂̃I���W�i����Rect�v���O����*/

/****�C���N���[�h****/
#include "MyRect.h"
/********************/


//�R���X�g���N�^
MyRect::MyRect()
{
	//�ϐ��̏�����
	_left = 0;
	_top = 0;
	_width = 0;
	_height = 0;
}

//�����t���R���X�g���N�^
MyRect::MyRect(float left, float top, float width, float height)
{
	//�����o�ϐ��Ɋi�[
	_left = left;
	_top = top;
	_width = width;
	_height = height;
}

//�f�X�g���N�^
MyRect::~MyRect()
{

}

//�����蔻��
//�m�[�h�ƃm�[�h
bool MyRect::IntersectsRect(MyRect targetRect)
{
	//4�̒��_�Ŕ��肷��
	if ((targetRect._left<_width&&targetRect._width>_left)&&(targetRect._top<_height&&targetRect._height>_top))
	{
		return true;
	}
	return false;
}

//�����蔻��
//�m�[�h�Ɠ_
bool MyRect::ContainsPoint(D3DXVECTOR3 targetPos)
{
	//4�̒��_�ƍ��W�Ŕ��肷��
	if (_left + _width > targetPos.x&&_left < targetPos.x&&_top + _height >targetPos.y&&_top < targetPos.y)
	{
		return true;
	}
	return false;
}