/*BackGround.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Sprite.h"
/********************************/


class BackGround : public Sprite
{
public:

	BackGround();
	~BackGround();

	//�w�i�쐬
	static BackGround *Create();
};

