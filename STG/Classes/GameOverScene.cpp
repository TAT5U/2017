//インクルード
#include "GameOverScene.h"
#include "TitleScene.h"

//日本語使用可
#pragma execution_character_set("utf-8")

//───────────────────────────
//コンストラクタ
//───────────────────────────
GameOverScene::GameOverScene()
{
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;


}

//───────────────────────────
//デストラクタ
//───────────────────────────
GameOverScene::~GameOverScene()
{



}

//───────────────────────────
//シーン作成
//引数：なし
//戻値：作成したシーンのアドレス
//───────────────────────────
Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

//───────────────────────────
//初期化（シーンの最初にやること）
//引数：なし
//戻値：初期化できたかどうか
//───────────────────────────
bool GameOverScene::init()
{
	//シーンができてなかったら中断
	if (!Layer::init())
	{
		return false;
	}
	auto GameOverlbl = Label::createWithTTF("GameOver!!", "fonts/arial.ttf", 50);
	GameOverlbl->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(GameOverlbl);

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
void GameOverScene::update(float dt)
{




}

//───────────────────────────
//入力処理
//引数：なし
//戻値：なし
//───────────────────────────
void GameOverScene::input()
{

	auto mauseListnere = EventListenerMouse::create();
	mauseListnere->onMouseDown = [=](Event* event)
	{
		EventMouse* mouse = (EventMouse*)event;
		if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
		{
			Director::getInstance()->replaceScene(TitleScene::createScene());
		}
		else if (mouse->getMouseButton() == MOUSE_BUTTON_RIGHT)
		{
			exit(1);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mauseListnere, this);

	//キーボードイベント
	auto keyListener = EventListenerKeyboard::create();

	//キーが押されたとき
	keyListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode==EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			exit(1);
		}
	};

	//キーボード監視
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

}