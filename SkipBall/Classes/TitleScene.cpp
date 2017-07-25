/*TitleScene.cpp*/

/*2017-06-01
	TAT5U
		�^�C�g���V�[��*/

#include "TitleScene.h"
#include "PlayScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");

TitleScene::TitleScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();
	
	//������
	bk = nullptr;
	title = nullptr;
	scorelbl = nullptr;
	listener = nullptr;
	trans = nullptr;
}

TitleScene::~TitleScene()
{

}

Scene* TitleScene::createScene()
{
	//�V�[���𐶐�
	Scene *scene = Scene::create();


	//���C������
	Layer *layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�w�i�\��
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//�^�C�g���\��
	{
		title = Sprite::create("images/Title.png");
		title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		title->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		this->addChild(title);
	}

	//�n�C�X�R�A�\��
	{
		Score sc;

		//�L�^��ǂݍ��񂾂Ƃ��A�܂��L�^���Ȃ��ꍇ�Ɂu���L�^�v�ƕ\��������
		if (sc.GetScore(0)==NULL)
		{
			scorelbl = Label::createWithSystemFont("High Score    ���L�^", "fonts/Marker Felt.ttf", 60);
			scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			scorelbl->setColor(Color3B::RED);

			//�e��t����
			scorelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
			scorelbl->setPosition(DisplaySize.width / 2, DisplaySize.height - title->getContentSize().height / 0.4f);
			this->addChild(scorelbl);
		}
		else
		{
			scorelbl = Label::createWithSystemFont("High Score    " + StringUtils::toString(sc.GetScore(0)) + "�b", "fonts/Marker Felt.ttf", 60);
			scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			scorelbl->setColor(Color3B::RED);

			//�e��t����
			scorelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
			scorelbl->setPosition(DisplaySize.width / 2, DisplaySize.height - title->getContentSize().height / 0.4f);
			this->addChild(scorelbl);
		}
	}

	input();
	this->scheduleUpdate();
	return true;
}

void TitleScene::update(float dt)
{

}

void TitleScene::input()
{
	//�^�b�`�C�x���g
	listener = EventListenerTouchOneByOne::create();

	//�^�b�`���n�߂��Ƃ�
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//�^�b�`�̈悪�^�C�g������������V�[���ڍs
		if (title->getBoundingBox().containsPoint(touch->getLocation()))
		{
			trans = TransitionFade::create(3.0f, PlayScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}

		return true;
	};

	//�^�b�`���邩�ǂ������Ď�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}