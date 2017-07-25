#include "PlayScene.h"

//追加ヘッダ
#include "GameOverScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()

PlayScene::PlayScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();

	//初期化
	cursor = nullptr;
	backGround = nullptr;
	pos = nullptr;
	workflg = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	anime = nullptr;
	anim = nullptr;
	animate = nullptr;
	remove = nullptr;
	action = nullptr;
	n = 3;
	i = 0;
	cnt = 0;
	score = 0;
	scoreText = nullptr;
	startTimeText = nullptr;
	speedFlg = false;
	timeFlg = false;
	textTimeFlg = false;
	startTime = 4;
	startTextTime = 3;
	cursorRect = Rect();

	//動的初期化
	{
		obj = new Sprite *[n];
		objpos = new Vec2[n];
		flg = new int[n];
		objRect = new Rect[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	//乱数
	srand(time(NULL));
}
PlayScene::~PlayScene()
{
	
}
Scene* PlayScene::createScene()
{
	//Scene作成
	Scene *scene{ Scene::create() };
	Layer *layer{ PlayScene::create() };
	scene->addChild(layer);
	return scene;
}
bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//最初のオブジェクト設定
	while (i<n)
	{
		//オブジェクト設定
		SetObj();
		i++;
	}

	//使用後初期化
	i = 0;

	//バックグラウンド表示
	{
		backGround = Sprite::create("images/bk.png");
		backGround->setPosition(Vec2(DisplaySize.width/2,DisplaySize.height/2));
		this->addChild(backGround,0);
	}

	//カーソル(basket)表示
	{
		cursor = Sprite::create("images/basket.png");
		cursor->setPosition(DisplaySize.width / 2, DisplaySize.height / 10);
		this->addChild(cursor,2);
	}

	//スコア表示
	{
		scoreText = Label::createWithSystemFont("SCORE " + StringUtils::toString(score), "fonts/AdobeHeitiStd-Regular.otf", 30);
		scoreText->setPosition(DisplaySize.width - 100, DisplaySize.height - 20);
		scoreText->setColor(Color3B::BLACK);
		this->addChild(scoreText,3);
	}

	input();
	this->scheduleUpdate();
	return true;
}
void PlayScene::update(float dt)
{
	//フェード中の待ち時間
	startTextTime -= dt;

	//オブジェクトの動作は停止
	if (textTimeFlg==false)
	{
		//フェードが終了したら表示
		if (startTextTime<=0)
		{
				startTimeText = Label::createWithSystemFont(StringUtils::toString((int)startTime), "fonts/AdobeHeitiStd-Regular.otf", 30);
				startTimeText->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
				startTimeText->setColor(Color3B::BLACK);
				this->addChild(startTimeText);
				textTimeFlg = true;
		}
	}
	else
	{
		//開始時間の秒数を減らす
		startTime -= dt;
		if (startTime <= 1)
		{
			//0になったら消去
			if (timeFlg == false)
			{
				startTimeText->removeFromParent();
				timeFlg = true;
			}

			//カーソルの範囲取得
			cursorRect = Rect(cursor->getPositionX() - 25, cursor->getPositionY() + (cursor->getPositionY() / 2), 50, 1);

			//オブジェクトの監視
			while (i<n)
			{
				//オブジェクトの範囲取得
				objRect[i] = obj[i]->getBoundingBox();

				//衝突判定
				if (objRect[i].intersectsRect(cursorRect))
				{
					//ボールの場合
					if (flg[i] == 1)
					{
						//スコア増
						score = score + 5;

						//一定個数入ったらスピード変更
						if (score>30)
						{
							speedFlg = true;
						}

						//スコア表示更新
						scoreText->setString("SCORE " + StringUtils::toString(score));

						//レベルアップカウント
						cnt++;

						//入った時のエフェクト
						anime = Sprite::create("images/star0000.png");
						anime->setPosition(obj[i]->getPosition());
						this->addChild(anime);
						anim = Animation::create();
						anim->addSpriteFrameWithFileName("images/star0001.png");
						anim->addSpriteFrameWithFileName("images/star0002.png");
						anim->addSpriteFrameWithFileName("images/star0003.png");
						anim->addSpriteFrameWithFileName("images/star0004.png");
						anim->addSpriteFrameWithFileName("images/star0005.png");
						anim->addSpriteFrameWithFileName("images/star0006.png");
						anim->addSpriteFrameWithFileName("images/star0007.png");
						anim->addSpriteFrameWithFileName("images/star0008.png");
						anim->addSpriteFrameWithFileName("images/star0009.png");
						anim->addSpriteFrameWithFileName("images/star0010.png");
						anim->addSpriteFrameWithFileName("images/star0011.png");
						anim->addSpriteFrameWithFileName("images/star0012.png");
						anim->addSpriteFrameWithFileName("images/star0013.png");
						anim->addSpriteFrameWithFileName("images/star0014.png");
						anim->setDelayPerUnit(0.06f);
						animate = Animate::create(anim);
						remove = RemoveSelf::create(true);
						action = Sequence::create(animate, remove, NULL);
						anime->runAction(action);

						//オブジェクトの消去
						obj[i]->removeFromParent();

						//オブジェクト設定
						SetObj();
					}

					//ボール以外
					else
					{
						//Scoreを利用可にする
						Score sc;

						//スコアを格納
						sc.SetScore(score);

						//シーン移行
						auto transition = TransitionFade::create(3.0f, GameOverScene::createScene());
						Director::getInstance()->replaceScene(transition);
						this->unscheduleUpdate();
					}
				}

				//落下速度
				FallObj();

				//画面外に出たらやり直し
				if (obj[i]->getPositionY() <= 0)
				{
					obj[i]->removeFromParent();
					SetObj();
				}

				//レベルアップ
				if (cnt >= 5)
				{
					i = 0;
					LvUpObj();
					cnt = 0;
				}
				i++;
			}

			//使用後初期化
			i = 0;
		}

		//開始時間更新
		else
		{
			startTimeText->setString(StringUtils::toString((int)startTime));
		}
	}
}
void PlayScene::input()
{
	//マウスイベント
	mouseListner = EventListenerMouse::create();
	mouseListner->onMouseMove = [=](Event *event)
	{
		//マウスカーソルイベント
		//カーソルはY軸固定
		mouse = (EventMouse *)event;
		cursor->setPosition(Point(mouse->getCursorX(), DisplaySize.height / 10) / EGL_SCALE);
	};

	//イベント監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}
//オブジェクト設定
void PlayScene::SetObj()
{
	//ランダムに変更
	flg[i] = rand() % (3 - 1 + 1) + 1;

	//ボール・紙くず・ビン
	if (flg[i] == 1)
	{
		obj[i] = Sprite::create("images/ball.png");
	}
	else if (flg[i] == 2)
	{
		obj[i] = Sprite::create("images/paper.png");
	}
	else if (flg[i] == 3)
	{
		obj[i] = Sprite::create("images/bin.png");
	}

	//速度レベル変更可の時のフラグ有効化
	spobjFlg[i] = true;

	//ランダムな位置にする
	obj[i]->setPosition(rand() % (((int)DisplaySize.width - 10) - 10 + 1), DisplaySize.height + 50);
	this->addChild(obj[i],1);
}
//レベルアップ時
void PlayScene::LvUpObj()
{
	workflg = new int[n];
	pos = new Vec2[n];
	while (i < n)
	{
		workflg[i] = flg[i];
		pos[i] = obj[i]->getPosition();
		obj[i]->removeFromParent();
		i++;
	}

	//使用後初期化
	i = 0;

	//オブジェクト数増加
	n++;

	//動的の解放と初期化
	{
		delete[]obj;
		delete[]flg;
		delete[]objRect;
		delete[]objpos;
		delete[]spFlg;
		delete[] spobjFlg;

		obj = new Sprite *[n];
		flg = new int[n];
		objRect = new Rect[n];
		objpos = new Vec2[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	while (i<n)
	{
		//最後
		if (i>=n-1)
		{
			//オブジェクト設定
			SetObj();
		}
		//最後以外 オブジェクトを変更させないため
		else
		{
			flg[i] = workflg[i];
			if (flg[i] == 1)
			{
				obj[i] = Sprite::create("images/ball.png");

			}
			else if (flg[i] == 2)
			{
				obj[i] = Sprite::create("images/paper.png");

			}
			else if (flg[i] == 3)
			{
				obj[i] = Sprite::create("images/bin.png");

			}

			//速度レベル変更可の時のフラグ有効化
			spobjFlg[i] = true;

			//位置を元の位置と同じに
			obj[i]->setPosition(pos[i]);
			this->addChild(obj[i],1);
		}
		i++;
	}

	//使用後初期化
	i = 0;

	//動的(work)の解放
	{
		delete[]workflg;
		delete[]pos;
	}
}
//落下速度
void PlayScene::FallObj()
{
	objpos[i] = obj[i]->getPosition();

	//最初の速度
	if (speedFlg==false)
	{
		objpos[i].y -= 3;

	}

	//速度レベル変更時
	else
	{
		//速度レベルを乱数で振り分け
		if (spobjFlg[i] == true)
		{
			spFlg[i] = rand() % (3 - 1 + 1) + 1;
		}
		if (spFlg[i] == 1)
		{
			objpos[i].y -= 2;
		}
		else if (spFlg[i] == 2)
		{
			objpos[i].y -= 5;
		}
		else if (spFlg[i] == 3)
		{
			objpos[i].y -= 1;
		}

		//画面外に出るまで速度レベルを変更しない
		spobjFlg[i] = false;
	}

	//落下先の位置を格納
	obj[i]->setPosition(objpos[i]);
}