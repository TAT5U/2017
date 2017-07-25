/*GameOverScene.cpp*/

/*2017-06-01
	TAT5U
		ゲームオーバーシーン*/

#include "GameOverScene.h"
#include "TitleScene.h"

#pragma execution_character_set("utf-8");

GameOverScene::GameOverScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();

	//初期化
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
	//シーンを生成
	Scene *scene = Scene::create();

	//レイヤ生成
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

	//背景表示
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//ゲームオーバー表示
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
	//タッチイベント
	listener = EventListenerTouchOneByOne::create();

	//タッチし始めたとき
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//タッチ領域がゲームオーバー内だったらシーン移行
		if (gameOver->getBoundingBox().containsPoint(touch->getLocation()))
		{
			trans = TransitionFade::create(3.0f, TitleScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}

		return true;
	};
	//タッチするかどうかを監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}