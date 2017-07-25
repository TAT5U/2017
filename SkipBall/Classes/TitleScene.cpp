/*TitleScene.cpp*/

/*2017-06-01
	TAT5U
		タイトルシーン*/

#include "TitleScene.h"
#include "PlayScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");

TitleScene::TitleScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();
	
	//初期化
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
	//シーンを生成
	Scene *scene = Scene::create();


	//レイヤ生成
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

	//背景表示
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//タイトル表示
	{
		title = Sprite::create("images/Title.png");
		title->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		title->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		this->addChild(title);
	}

	//ハイスコア表示
	{
		Score sc;

		//記録を読み込んだとき、まだ記録がない場合に「未記録」と表示させる
		if (sc.GetScore(0)==NULL)
		{
			scorelbl = Label::createWithSystemFont("High Score    未記録", "fonts/Marker Felt.ttf", 60);
			scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			scorelbl->setColor(Color3B::RED);

			//影を付ける
			scorelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
			scorelbl->setPosition(DisplaySize.width / 2, DisplaySize.height - title->getContentSize().height / 0.4f);
			this->addChild(scorelbl);
		}
		else
		{
			scorelbl = Label::createWithSystemFont("High Score    " + StringUtils::toString(sc.GetScore(0)) + "秒", "fonts/Marker Felt.ttf", 60);
			scorelbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			scorelbl->setColor(Color3B::RED);

			//影を付ける
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
	//タッチイベント
	listener = EventListenerTouchOneByOne::create();

	//タッチし始めたとき
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//タッチ領域がタイトル内だったらシーン移行
		if (title->getBoundingBox().containsPoint(touch->getLocation()))
		{
			trans = TransitionFade::create(3.0f, PlayScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}

		return true;
	};

	//タッチするかどうかを監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}