/*WallDraw.cpp*/

/*2017-06-01
	TAT5U
		�ǂ����I�u�W�F�N�g�w�����ۂ�������*/

#include "WallDraw.h"

#pragma execution_character_set("utf-8");

WallDraw::WallDraw()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();
	
	//������
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

	//�ǂ̕\��(��E�E�E��)
	{
		//��
		WallUp = Sprite::create();
		WallUp->setPosition(DisplaySize.width / 2, DisplaySize.height);
		WallUp->setTextureRect(Rect(0, 0, DisplaySize.width, 0));
		WUPhysic = PhysicsBody::createBox(WallUp->getContentSize());
		WUPhysic->setDynamic(false);
		WUPhysic->setRotationEnable(false);
		WallUp->setPhysicsBody(WUPhysic);
		this->addChild(WallUp);

		//�E
		WallRight = Sprite::create();
		WallRight->setPosition(DisplaySize.width, DisplaySize.height / 2);
		WallRight->setTextureRect(Rect(0, 0, 0, DisplaySize.height));
		WRPhysic = PhysicsBody::createBox(WallRight->getContentSize());
		WRPhysic->setDynamic(false);
		WallRight->setPhysicsBody(WRPhysic);
		this->addChild(WallRight);
		
		//��
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
