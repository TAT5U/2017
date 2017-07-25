/*WallDraw.cpp*/

/*2017-06-01
	TAT5U
		壁だけオブジェクト指向っぽく分けた*/

#include "WallDraw.h"

#pragma execution_character_set("utf-8");

WallDraw::WallDraw()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();
	
	//初期化
	WallUp = nullptr;
	WallRight = nullptr;
	WallLeft = nullptr;
	WUPhysic = nullptr;
	WRPhysic = nullptr;
	WLPhysic = nullptr;
}

WallDraw::~WallDraw()
{

}

bool WallDraw::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//壁の表示(上・右・左)
	{
		//上
		WallUp = Sprite::create();
		WallUp->setPosition(DisplaySize.width / 2, DisplaySize.height);
		WallUp->setTextureRect(Rect(0, 0, DisplaySize.width, 0));
		WUPhysic = PhysicsBody::createBox(WallUp->getContentSize());
		WUPhysic->setDynamic(false);
		WUPhysic->setRotationEnable(false);
		WallUp->setPhysicsBody(WUPhysic);
		this->addChild(WallUp);

		//右
		WallRight = Sprite::create();
		WallRight->setPosition(DisplaySize.width, DisplaySize.height / 2);
		WallRight->setTextureRect(Rect(0, 0, 0, DisplaySize.height));
		WRPhysic = PhysicsBody::createBox(WallRight->getContentSize());
		WRPhysic->setDynamic(false);
		WallRight->setPhysicsBody(WRPhysic);
		this->addChild(WallRight);
		
		//左
		WallLeft = Sprite::create();
		WallLeft->setPosition(0, DisplaySize.height / 2);
		WallLeft->setTextureRect(Rect(0, 0, 0, DisplaySize.height));
		WLPhysic = PhysicsBody::createBox(WallLeft->getContentSize());
		WLPhysic->setDynamic(false);
		WallLeft->setPhysicsBody(WLPhysic);
		this->addChild(WallLeft);
	}
	return true;
}
