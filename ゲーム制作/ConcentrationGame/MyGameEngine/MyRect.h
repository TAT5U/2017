/*MyRect.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Global.h"
#include "Input.h"
/********************/


//cocos2dx�̂悤�Ȕ͈͎w��̏�������������
//�������g�p�ł���悤�ɂ��邽�߂̃I���W�i����Rect�N���X
class MyRect
{
public:

	//�e���W
	float _left;
	float _top;
	float _width;
	float _height;

	//�R���X�g���N�^
	MyRect();

	//�����cocos2dx�̂悤�ɋL�q�ł���
	//�����t���R���X�g���N�^
	//����->���E��E���E����
	//�ߒl->�Ȃ�
	MyRect(float left, float top, float width, float height);

	//�f�X�g���N�^
	~MyRect();

	/****************�����蔻��****************/

	//�m�[�h�ƃm�[�h
	bool IntersectsRect(MyRect targetRect);

	//�m�[�h�Ɠ_
	bool ContainsPoint(D3DXVECTOR3 targetPos);
	bool ContainsPoint(Point targetPt);
	/******************************************/
};