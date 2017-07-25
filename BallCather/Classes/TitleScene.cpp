/*TitleScene.cpp*/

/*2017-02-17
		TAT5U
			タイトルシーン*/

#include "TitleScene.h"

//追加ヘッダ
#include "PlayScene.h"

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()
TitleScene::TitleScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();

	//初期化
	title = nullptr;
	start = nullptr;
	backGround = nullptr;
	labelFD = nullptr;
	cursor = nullptr;
	select = nullptr;
	select2 = nullptr;
	startButton = nullptr;
	startMenu = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	transition = nullptr;
	startRect = Rect();
	cursorRect = Rect();
	selectflg = false;
}
TitleScene::~TitleScene()
{

}
Scene* TitleScene::createScene()
{
	//Scene作成
	Scene *scene{ Scene::create() };
	Layer *layer{ TitleScene::create() };
	scene->addChild(layer);
	return scene;
}
bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//バックグラウンド表示
	{
		backGround = Sprite::create("images/bk.png");
		backGround->setPosition(Vec2(DisplaySize.width / 2, DisplaySize.height / 2));
		this->addChild(backGround, 0);
	}

	//タイトル表示
	{
		title = Label::createWithTTF("BallCatcher", "fonts/AdobeHeitiStd-Regular.otf", 50);
		title->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		title->setColor(Color3B::BLACK);
		this->addChild(title);

	}

	//スタート表示
	{
		start = Label::createWithTTF("START!!", "fonts/AdobeHeitiStd-Regular.otf", 50);
		startButton = MenuItemLabel::create(start, CC_CALLBACK_1(TitleScene::ClickStart, this));
		startMenu = Menu::create(startButton, NULL);
		startMenu->setPosition(DisplaySize.width / 2-10, DisplaySize.height / 2-title->getContentSize().height);
		startMenu->setColor(Color3B::BLACK);
		this->addChild(startMenu);
	}

	//下地をスタートラベルに(非表示)
	{
		labelFD = Sprite::create();
		labelFD->setTextureRect(Rect(0, 0, start->getContentSize().width, start->getContentSize().height / 2));
		labelFD->setPosition(DisplaySize.width / 2-10, DisplaySize.height / 2 - title->getContentSize().height/1.3);
		this->addChild(labelFD);
		labelFD->setVisible(false);
		startRect = labelFD->getBoundingBox();
	}

	//カーソルのラベル(非表示)
	{
		cursor = Sprite::create();
		cursor->setTextureRect(Rect(0, 0, 10, 10));
		this->addChild(cursor);
		cursor->setVisible(false);
	}

	input();
	this->scheduleUpdate();
	return true;
}
void TitleScene::update(float dt)
{
	//マウスイベント
	mouseListner = EventListenerMouse::create();
	mouseListner->onMouseMove = [=](Event *event)
	{
		//マウスカーソルイベント
		mouse = (EventMouse *)event;
		cursor->setPosition(Point(mouse->getCursorX(), mouse->getCursorY()) / EGL_SCALE);

		//カーソルの範囲
		cursorRect = cursor->getBoundingBox();

		//カーソルとスタートが重なったとき
		if (cursorRect.intersectsRect(startRect))
		{
			//select表示
			if (selectflg == false)
			{
				select = Sprite::create("images/select.png");
				select->setPosition(labelFD->getPositionX()-120,labelFD->getPositionY());
				this->addChild(select);

				select2 = Sprite::create("images/select.png");
				select2->setRotation(180);
				select2->setPosition(labelFD->getPositionX() + labelFD->getContentSize().width/1.4, labelFD->getPositionY());
				this->addChild(select2);
				selectflg = true;
			}
		}
		else
		{
			//エラー対策
			if (selectflg==true)
			{
				select->removeFromParent();
				select2->removeFromParent();
				selectflg = false;
			}
		}
	};

	//イベント監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}
void TitleScene::input()
{

}

//クリックした時
void TitleScene::ClickStart(Ref *pSender)
{
	//シーン移行
	transition = TransitionFade::create(3.0f, PlayScene::createScene());
	Director::getInstance()->replaceScene(transition);
	this->unscheduleUpdate();
}