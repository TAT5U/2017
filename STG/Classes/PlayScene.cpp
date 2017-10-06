//インクルード
#include "PlayScene.h"
#include"ClearScene.h"
#include "GameOverScene.h"


//追加
#include<time.h>
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()
#include "SimpleAudioEngine.h" 
// 制限 時間
const float TIME_LIMIT_SECOND = 60;
const float START_TIME = 4;


//日本語使用可
#pragma execution_character_set("utf-8")
using namespace std;
//───────────────────────────
//コンストラクタ
//───────────────────────────
PlayScene::PlayScene()
	:_second(TIME_LIMIT_SECOND)
,_startTime(START_TIME)
{
	//ウィンドウのサイズ取得&機体の初期位置設定
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;
	cursorY = DisplaySizeHeight / 10;

	//カウントの初期化
	i = 0;

	//乱数初期化+空回し
	srand(time(NULL));
	rand(); rand(); rand(); rand(); rand();

	//倒した敵のカウントを初期化
	EnemyDeadCount = 0;
	EnemyCount = 0;

	//敵の生存フラグをすべて生存にする&移動先の初期化
	while (i<3)
	{
		_isEnemyDead[i] = false;
		EnemyFlgposX[i] = 0;
		EnemyFlgposY[i] = 0;
		i++;
	}
	//再利用のため初期化
	i = 0;
	startTimeTextflg = false;
}

//───────────────────────────
//デストラクタ
//───────────────────────────
PlayScene::~PlayScene()
{
}

//───────────────────────────
//シーン作成
//引数：なし
//戻値：作成したシーンのアドレス
//───────────────────────────
Scene* PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}

//───────────────────────────
//初期化（シーンの最初にやること）
//引数：なし
//戻値：初期化できたかどうか
//───────────────────────────
bool PlayScene::init()
{
	//シーンができてなかったら中断
	if (!Layer::init())
	{
		return false;
	}
	//効果音プリロード
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bomb.wav");



	//機体の宣言
	{
		auto cursor = Sprite::create("player.png");
		cursor->setPosition(DisplaySizeWidth / 2, cursorY);
		this->addChild(cursor);
		_cursor = cursor;
	}


	
	//敵の宣言
	while (i < 3)
	{
		auto enemy = Sprite::create("enemy.png");

		//乱数を使用した位置
		//横 画面から50引いたところから50足したところまでの範囲
		EnemyFlgposX[i] = rand() % (((int)DisplaySizeWidth - 50) - 50 + 1) + 50;
		//縦 画面から50引いたところから機体+100のところまでの範囲
		EnemyFlgposY[i] = rand() % (((int)DisplaySizeHeight - 50) - (cursorY + 100) + 1) + (cursorY + 100);
		enemy->setPosition(EnemyFlgposX[i], EnemyFlgposY[i]);

		this->addChild(enemy);
		_enemy[i] = enemy;
		_isEnemyDead[i] = false;
		EnemyCount++;
		i++;
	}
	//再利用のため初期化
	i = 0;

	int second = static_cast < int >(_second); // int 型 に キャスト する
	secondText = Label::createWithSystemFont("制限時間 " + StringUtils::toString(second) + " 秒", "fonts/arial.ttf", 20);
	secondText->setPosition(DisplaySizeWidth / 6, DisplaySizeHeight - DisplaySizeHeight / 20);
	this->addChild(secondText);

	int startTime = static_cast <int>(_startTime);
	startTimeText=Label::createWithSystemFont( StringUtils::toString(startTime), "fonts/arial.ttf", 80);
	startTimeText->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(startTimeText);
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
void PlayScene::update(float dt)
{
	_startTime -= dt;
	int startTime = static_cast <int>(_startTime);
	if (startTime<=0)
	{
		if (startTimeTextflg==false)
		{
			//弾の宣言
			{
				auto bullet = Sprite::create("bullet.png");
				bullet->setPosition(_cursor->getPositionX(), cursorY);
				this->addChild(bullet);
				_bullet = bullet;
			}
			startTimeText->removeFromParent();
			startTimeTextflg = true;
		}

		// 残り 秒 数 を 減らす
		_second -= dt;
		// 残り 秒 数 の 表示 を 更新 する
		int second = static_cast < int >(_second); // int 型 に キャスト する
		secondText->setString("制限時間 " + StringUtils::toString(second) + " 秒");


		if (second <= 0)
		{
			auto transition = TransitionFade::create(3.0f, GameOverScene::createScene());
			Director::getInstance()->replaceScene(transition);
			this->unscheduleUpdate();
		}
		//弾の移動
		Vec2 bulletpos = _bullet->getPosition();
		bulletpos.y += 10;
		_bullet->setPosition(bulletpos);

		//弾が画面外にいったらまた出す
		if (_bullet->getPositionY() > DisplaySizeHeight)
		{
			_bullet->setPosition(_cursor->getPositionX(), cursorY);
		}

		//弾の衝突の判定を格納
		Rect bulletRect = _bullet->getBoundingBox();
		while (i<3)
		{
			if (_isEnemyDead[i] == true)
			{

			}
			else
			{
				//指定したところまで移動し終えたとき次の移動先を指定
				if (_enemy[i]->getPositionX() == EnemyFlgposX[i] && _enemy[i]->getPositionY() == EnemyFlgposY[i])
				{
					EnemyFlgposX[i] = rand() % (((int)DisplaySizeWidth - 50) - 50 + 1) + 50;
					EnemyFlgposY[i] = rand() % (((int)DisplaySizeHeight - 50) - (cursorY + 100) + 1) + (cursorY + 100);
					auto move = MoveTo::create(rand() % 3 + 1, Point(EnemyFlgposX[i], EnemyFlgposY[i]));
					_enemy[i]->runAction(move);
				}
				//衝突判定で敵を消す
				Rect enemyRect = _enemy[i]->getBoundingBox();
				if (bulletRect.intersectsRect(enemyRect))
				{
					//爆発
					auto bomb = Sprite::create("bomb0000.png");
					bomb->setPosition(_enemy[i]->getPosition());
					this->addChild(bomb);

					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomb.wav");
					auto anim = Animation::create();
					anim->addSpriteFrameWithFileName("bomb0001.png");
					anim->addSpriteFrameWithFileName("bomb0002.png");
					anim->addSpriteFrameWithFileName("bomb0003.png");
					anim->addSpriteFrameWithFileName("bomb0004.png");
					anim->addSpriteFrameWithFileName("bomb0005.png");
					anim->addSpriteFrameWithFileName("bomb0006.png");
					anim->addSpriteFrameWithFileName("bomb0007.png");
					anim->setDelayPerUnit(0.06f);
					auto animate = Animate::create(anim);
					auto removebomb = RemoveSelf::create(true);
					auto bombAction = Sequence::create(animate, removebomb, NULL);
					bomb->runAction(bombAction);


					//敵を消す
					_enemy[i]->removeFromParent();
					_isEnemyDead[i] = true;
					EnemyDeadCount++;
				}
			}
			i++;
		}
		//再利用のため初期化
		i = 0;

		//敵がすべて消えたらクリア画面
		if (EnemyDeadCount == EnemyCount)
		{
			auto transition = TransitionFade::create(3.0f, ClearScene::createScene());
			Director::getInstance()->replaceScene(transition);
			this->unscheduleUpdate();
		}
	}
	else
	{
		startTimeText->setString(StringUtils::toString(startTime));
	}
	
}

//───────────────────────────
//入力処理
//引数：なし
//戻値：なし
//───────────────────────────
void PlayScene::input()
{
	auto mauseListnere = EventListenerMouse::create();
	mauseListnere->onMouseMove = [=](Event* event)
	{
		EventMouse* mouse = (EventMouse*)event;
		_cursor->setPosition(Point(mouse->getCursorX(), cursorY) / EGL_SCALE);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mauseListnere, this);
	
	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = [=](Touch* touc, Event* eve)
	{
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
}