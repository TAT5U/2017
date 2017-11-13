/*BackGround.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Sprite.h"
/********************************/


class BackGround : public Sprite
{
public:

	BackGround();
	~BackGround();

	//背景作成
	static BackGround *Create();
};

