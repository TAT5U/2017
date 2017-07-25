/*GameOverScene.cpp*/

/*2017-02-17
		TAT5U
			ゲームオバーシーン*/
			
#include "GameOverScene.h"

//追加ヘッダ
#include "TitleScene.h"
#include "RankScene.h"

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()

GameOverScene::GameOverScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();

	//初期化
	gameOver = nullptr;
	score = nullptr;
	backGround = nullptr;
	labelFD = nullptr;
	labelFD2 = nullptr;
	cursor = nullptr;
	select = nullptr;
	select2 = nullptr;
	select3 = nullptr;
	select4 = nullptr;
	gameOverButton = nullptr;
	scoreButton = nullptr;
	gameOverMenu = nullptr;
	scoreMenu = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	transition = nullptr;
	scoreRect = Rect();
	gameOverRect = Rect();
	cursorRect = Rect();
	selectflg = false;
	selectflg2 = false;
}
GameOverScene::~GameOverScene()
{

}
Scene* GameOverScene::createScene()
{
	//Scene作成
	Scene *scene{ Scene::create() };
	Layer *layer{ GameOverScene::create() };
	scene->addChild(layer);
	return scene;
}
bool GameOverScene::init()
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

	//ゲームオーバー表示
	{
		gameOver = Label::createWithTTF("GameOver!!", "fonts/AdobeHeitiStd-Regular.otf", 50);
		gameOverButton = MenuItemLabel::create(gameOver, CC_CALLBACK_1(GameOverScene::ClickGameOver, this));
		gameOverMenu = Menu::create(gameOverButton, NULL);
		gameOverMenu->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		gameOverMenu->setColor(Color3B::BLACK);
		this->addChild(gameOverMenu);
	}

	//スコア表示
	{
		score = Label::createWithSystemFont("SCORE", "fonts/AdobeHeitiStd-Regular.otf", 50);
		scoreButton = MenuItemLabel::create(score, CC_CALLBACK_1(GameOverScene::ClickScore, this));
		scoreMenu = Menu::create(scoreButton, NULL);
		scoreMenu->setPosition(gameOverMenu->getPositionX()-10,gameOverMenu->getPositionY()-gameOverMenu->getScaleY()-70);
		scoreMenu->setColor(Color3B::BLACK);
		this->addChild(scoreMenu);
	}

	//下地をスコアラベルに(非表示)
	{
		labelFD = Sprite::create();
		labelFD->setTextureRect(Rect(0, 0, score->getContentSize().width, score->getContentSize().height / 2));
		labelFD->setPosition(gameOverMenu->getPositionX() - 10, gameOverMenu->getPositionY() - gameOverMenu->getScaleY() - 70);
		this->addChild(labelFD);
		labelFD->setVisible(false);
		scoreRect = labelFD->getBoundingBox();
	}

	//下地をゲームオーバーラベルに(非表示)
	{
		labelFD2 = Sprite::create();
		labelFD2->setTextureRect(Rect(0, 0, gameOver->getContentSize().width, gameOver->getContentSize().height / 2));
		labelFD2->setPosition(DisplaySize.width / 2, DisplaySize.height / 2+20);
		this->addChild(labelFD2);
		labelFD2->setVisible(false);
		gameOverRect = labelFD2->getBoundingBox();
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
void GameOverScene::update(float dt)
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

		//カーソルとスコアが重なったとき
		if (cursorRect.intersectsRect(scoreRect))
		{
			//select表示
			if (selectflg == false)
			{
				select = Sprite::create("images/select.png");
				select->setPosition(labelFD->getPositionX() - 120, labelFD->getPositionY());
				this->addChild(select);

				select2 = Sprite::create("images/select.png");
				select2->setRotation(180);
				select2->setPosition(labelFD->getPositionX() + labelFD->getContentSize().width / 1.4, labelFD->getPositionY());
				this->addChild(select2);
				selectflg = true;
			}
		}
		else
		{
			//エラー対策
			if (selectflg == true)
			{
				select->removeFromParent();
				select2->removeFromParent();
				selectflg = false;
			}
		}

		//カーソルとゲームオーバーが重なったとき
		if (cursorRect.intersectsRect(gameOverRect))
		{
			//select表示
			if (selectflg2 == false)
			{
				select3 = Sprite::create("images/select.png");
				select3->setPosition(labelFD2->getPositionX() - 180, labelFD2->getPositionY());
				this->addChild(select3);

				select4 = Sprite::create("images/select.png");
				select4->setRotation(180);
				select4->setPosition(labelFD2->getPositionX() + labelFD2->getContentSize().width / 1.5, labelFD2->getPositionY());
				this->addChild(select4);
				selectflg2 = true;
			}
		}
		else
		{
			//エラー対策
			if (selectflg2 == true)
			{
				select3->removeFromParent();
				select4->removeFromParent();
				selectflg2 = false;
			}
		}
	};

	//イベント監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}
void GameOverScene::input()
{

}
//クリックした時
void GameOverScene::ClickGameOver(Ref *pSender)
{
	//シーン移行
	transition = TransitionFade::create(3.0f, TitleScene::createScene());
	Director::getInstance()->replaceScene(transition);
	this->unscheduleUpdate();
}
//クリックした時
void GameOverScene::ClickScore(Ref *pSender)
{
	//シーン移行
	transition = TransitionFade::create(3.0f, RankScene::createScene());
	Director::getInstance()->replaceScene(transition);
	this->unscheduleUpdate();
}