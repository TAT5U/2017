/*Light.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include"Node.h"
/********************/


//���C�g���g�p���邽�߂̃N���X
//Node�N���X���p��
class Light : public Node
{
public:

	//�f�X�g���N�^
	~Light();

	//�ÓI�֐�	���C�g�̍쐬
	//����->�Ȃ�
	//�ߒl->���C�g
	static Light *Create();
};

