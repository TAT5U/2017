/*BackGround.cpp*/

#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{
}

//�w�i�쐬
BackGround *BackGround::Create()
{
	Sprite *backGround = Sprite::Create("Assets//BackGround.png");
	backGround->SetPosition(g.STANDARD_CONTENT_WIDTH, g.STANDARD_CONTENT_HEIGHT);
	return static_cast<BackGround*>(backGround);
}
