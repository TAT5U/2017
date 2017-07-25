/*GameClearScene.cpp*/

/*2017-06-01
	TAT5U
		ゲームクリアシーン*/

#include "GameClearScene.h"
#include "TitleScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");

GameClearScene::GameClearScene()
{
	//ウィンドウサイズ取得
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
	//シーンを生成
	Scene *scene = Scene::create();

	//レイヤ生成
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

	//背景表示
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//ゲームクリア表示
	{
		gameClear = Sprite::create("images/GameClear.png");
		gameClear->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		gameClear->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		this->addChild(gameClear);
	}

	//スコア表示
	{
		Score sc;

		//記録を読み込んで表示
		scorelbl = Label::createWithSystemFont("Your Score    " + StringUtils::toString(sc.GetScore(1)) + "秒", "fonts/Marker Felt.ttf", 60);
		scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		scorelbl->setColor(Color3B::RED);

		//影を付ける
		scorelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
		scorelbl->setPosition(DisplaySize.width / 2, DisplaySize.height - gameClear->getContentSize().height / 0.4f);
		this->addChild(scorelbl);

		//新記録なら「新記録!!」と表示
		if (sc.GetScore(0) == sc.GetScore(1))
		{
			newRecordlbl = Label::createWithSystemFont("新記録!!", "fonts/Marker Felt.ttf", 60);
			newRecordlbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			newRecordlbl->setColor(Color3B::YELLOW);

			//影を付ける
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
	//タッチイベント
	listener = EventListenerTouchOneByOne::create();

	//タッチし始めたとき
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//タッチ領域がゲームクリア内だったらシーン移行
		if (gameClear->getBoundingBox().containsPoint(touch->getLocation()))
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