/*GameClearScene.cpp*/

/*2017-06-01
	TAT5U
		�Q�[���N���A�V�[��*/

#include "GameClearScene.h"
#include "TitleScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");

GameClearScene::GameClearScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	bk = nullptr;
	gameClear = nullptr;
	scorelbl = nullptr;
	newRecordlbl = nullptr;
	listener = nullptr;
	trans = nullptr;
}

GameClearScene::~GameClearScene()
{

}

Scene* GameClearScene::createScene()
{
	//�V�[���𐶐�
	Scene *scene = Scene::create();

	//���C������
	Layer *layer = GameClearScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameClearScene::init()
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

	//�Q�[���N���A�\��
	{
		gameClear = Sprite::create("images/GameClear.png");
		gameClear->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		gameClear->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		this->addChild(gameClear);
	}

	//�X�R�A�\��
	{
		Score sc;

		//�L�^��ǂݍ���ŕ\��
		scorelbl = Label::createWithSystemFont("Your Score    " + StringUtils::toString(sc.GetScore(1)) + "�b", "fonts/Marker Felt.ttf", 60);
		scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		scorelbl->setColor(Color3B::RED);

		//�e��t����
		scorelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
		scorelbl->setPosition(DisplaySize.width / 2, DisplaySize.height - gameClear->getContentSize().height / 0.4f);
		this->addChild(scorelbl);

		//�V�L�^�Ȃ�u�V�L�^!!�v�ƕ\��
		if (sc.GetScore(0) == sc.GetScore(1))
		{
			newRecordlbl = Label::createWithSystemFont("�V�L�^!!", "fonts/Marker Felt.ttf", 60);
			newRecordlbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			newRecordlbl->setColor(Color3B::YELLOW);

			//�e��t����
			newRecordlbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
			newRecordlbl->setPosition(DisplaySize.width / 2, DisplaySize.height - gameClear->getContentSize().height / 0.455f);
			this->addChild(newRecordlbl);
		}
	}

	input();
	this->scheduleUpdate();
	return true;
}

void GameClearScene::update(float dt)
{

}

void GameClearScene::input()
{
	//�^�b�`�C�x���g
	listener = EventListenerTouchOneByOne::create();

	//�^�b�`���n�߂��Ƃ�
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//�^�b�`�̈悪�Q�[���N���A����������V�[���ڍs
		if (gameClear->getBoundingBox().containsPoint(touch->getLocation()))
		{
			trans = TransitionFade::create(3.0f, TitleScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}
		return true;
	};
	//�^�b�`���邩�ǂ������Ď�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}