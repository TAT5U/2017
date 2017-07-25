/*GameOverScene.cpp*/

/*2017-06-01
	TAT5U
		�Q�[���I�[�o�[�V�[��*/

#include "GameOverScene.h"
#include "TitleScene.h"

#pragma execution_character_set("utf-8");

GameOverScene::GameOverScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	//������
	bk = nullptr;
	gameOver = nullptr;
	listener = nullptr;
	trans = nullptr;
}

GameOverScene::~GameOverScene()
{

}

Scene* GameOverScene::createScene()
{
	//�V�[���𐶐�
	Scene *scene = Scene::create();

	//���C������
	Layer *layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
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

	//�Q�[���I�[�o�[�\��
	{
		gameOver = Sprite::create("images/GameOver.png");
		gameOver->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		gameOver->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		this->addChild(gameOver);
	}

	input();
	this->scheduleUpdate();
	return true;
}

void GameOverScene::update(float dt)
{

}

void GameOverScene::input()
{
	//�^�b�`�C�x���g
	listener = EventListenerTouchOneByOne::create();

	//�^�b�`���n�߂��Ƃ�
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//�^�b�`�̈悪�Q�[���I�[�o�[����������V�[���ڍs
		if (gameOver->getBoundingBox().containsPoint(touch->getLocation()))
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