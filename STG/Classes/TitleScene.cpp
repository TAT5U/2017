//インクルード
#include "TitleScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h" 

//日本語使用可
#pragma execution_character_set("utf-8")
USING_NS_CC;
//───────────────────────────
//コンストラクタ
//───────────────────────────
TitleScene::TitleScene()
{
	//マウスカーソル非表示
	ShowCursor(false);
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;
	//BGMプリロード
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);
}

//───────────────────────────
//デストラクタ
//───────────────────────────
TitleScene::~TitleScene()
{



}

//───────────────────────────
//シーン作成
//引数：なし
//戻値：作成したシーンのアドレス
//───────────────────────────
Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

//───────────────────────────
//初期化（シーンの最初にやること）
//引数：なし
//戻値：初期化できたかどうか
//───────────────────────────
bool TitleScene::init()
{
	//シーンができてなかったら中断
	if (!Layer::init())
	{
		return false;
	}

	auto Title = Label::createWithTTF("Shooting Game\n     START!!", "fonts/arial.ttf", 50);
	Title->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(Title);
	//入力処理
	input();

	//定期的にupdate関数を呼ぶ
	this->scheduleUpdate();

	return true;
}

//───────────────────────────
//更新（常にやること）
//引数：dt　前回更新してからの時間（秒）
//戻値：なし
//───────────────────────────
void TitleScene::update(float dt)
{




}

//───────────────────────────
//入力処理
//引数：なし
//戻値：なし
//───────────────────────────
void TitleScene::input()
{


	    //タッチイベント
    auto listener = EventListenerTouchOneByOne::create();

    //画面をタッチしたとき
    listener->onTouchBegan = [this](Touch* touch, Event* event)
    {
		//auto transition = TransitionFade::create(3.0f, PlayScene::createScene());
		//Director::getInstance()->replaceScene(transition);
		//this->unscheduleUpdate();
		Director::getInstance()->replaceScene(PlayScene::createScene());
		return true;
    };

    //タッチ監視
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}