/*PlayScene.cpp*/

/*2017-06-01
	TAT5U
		プレイシーン*/

#include "PlayScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "WallDraw.h"
#include "Score.h"

//ステージの数
#define StageMax 3

//ボスステージをクリアするまでのカウント
#define Boss_Stage 2

//制限時間
#define Time 120;

//ゲーム開始までの時間
#define Delay 3;

#pragma execution_character_set("utf-8");

PlayScene::PlayScene()
{
	//ウィンドウサイズ取得
	DisplaySize = Director::getInstance()->getVisibleSize();

	//初期化
	Stage = nullptr;
	Ball = nullptr;
	Goal = nullptr;
	Fake1 = nullptr;
	Fake2 = nullptr;
	Fake3 = nullptr;
	bk = nullptr;
	timelbl = nullptr;
	BallPhysic = nullptr;
	GoalPhysic = nullptr;
	StagePhysic = nullptr;
	Fake1Physic = nullptr;
	Fake2Physic = nullptr;
	Fake3Physic = nullptr;
	StageShape = nullptr;
	GoalShape = nullptr;
	Fake1Shape = nullptr;
	Fake2Shape = nullptr;
	Fake3Shape = nullptr;
	BallRect = Rect();
	TouchPos = Vec2();
	BallPos = Vec2();
	BallNode = nullptr;
	StageNum = 1;
	BossCnt = 0;
	ContactTime = 999;
	StageName = string();
	fakeflg = false;
	scheduleflg = true;
	contactflg = false;
	TouchFlg = false;
	delayflg = false;
	listener = nullptr;
	physicsContact = nullptr;
	contact = nullptr;
	trans = nullptr;
	time = Time;
	dtime = Delay;
}

PlayScene::~PlayScene()
{
	
}

Scene* PlayScene::createScene()
{
	//シーンを重力付きで生成
	Scene *scene = Scene::createWithPhysics();
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0, -500));
	world->setSpeed(1.0f);
	
	//レイヤ生成
	Layer *layer = PlayScene::create();
	Layer *WallLayer = WallDraw::create();
	scene->addChild(layer);
	scene->addChild(WallLayer);
	return scene;
}

bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//最初のステージ名を格納
	StageName = "St0" + to_string(StageNum);

	//各PhysicsShapeCacheを利用できるようにする
	StageShape = PhysicsShapeCache::getInstance();
	GoalShape = PhysicsShapeCache::getInstance();
	Fake1Shape = PhysicsShapeCache::getInstance();
	Fake2Shape = PhysicsShapeCache::getInstance();
	Fake3Shape = PhysicsShapeCache::getInstance();

	//背景表示
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//制限時間表示
	{
		timelbl = Label::createWithSystemFont(StringUtils::toString((int)time) + "秒", "fonts/arial.ttf", 100);
		timelbl->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		timelbl->setPosition(DisplaySize.width, DisplaySize.height);

		//影を付ける
		timelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
		this->addChild(timelbl,999);
	}

	//ステージのプロパティリストを読み込む
	StageShape->addShapesWithFile("plist/"+StageName+".plist");

	//ステージ表示
	{
		Stage = Sprite::create("images/"+StageName+".png");

		//ステージの物理エンジンを格納する
		StagePhysic = StageShape->setPhysics(StageName, Stage);
		Stage->setPhysicsBody(StagePhysic);

		Stage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		Stage->setPosition(0, 0);
		this->addChild(Stage);
	}

	//ゴールのプロパティリストを読み込む
	GoalShape->addShapesWithFile("plist/"+StageName+"Goal.plist");

	//ゴール表示
	{
		Goal = Sprite::create("images/"+StageName+"Goal.png");

		//ゴールの物理エンジンを格納する
		GoalPhysic = GoalShape->setPhysics(StageName+"Goal", Goal);

		//衝突判定するために識別子を格納する
		GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
		GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
		GoalPhysic->setContactTestBitmask(INT_MAX);

		Goal->setPhysicsBody(GoalPhysic);
		Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		Goal->setPosition(0, 0);
		this->addChild(Goal);

		//自分自身にタグ付けする
		Goal->setTag(static_cast<int>(PhysicName::Goal));
	}

	//ボール表示
	{
		Ball = Sprite::create("images/ball.png");

		Ball->setPosition(10, DisplaySize.height / 2);
		BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);

		//衝突判定するために識別子を格納する
		BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
		BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
		BallPhysic->setContactTestBitmask(INT_MAX);

		Ball->setPhysicsBody(BallPhysic);
		this->addChild(Ball);

		//自分自身にタグ付けする
		Ball->setTag(static_cast<int>(PhysicName::Ball));
	}
	input();
	this->scheduleUpdate();
	return true;
}

void PlayScene::update(float dt)
{
	//ゲームが開始したら
	if (delayflg==true)
	{
		//ステージ変更していないとき
		if (scheduleflg == true)
		{
			//ボールがない場合
			if (Ball == NULL)
			{
				Ball = Sprite::create("images/ball.png");

				//ボスステージの最後のモードになっているとき
				if (BossCnt>3)
				{
					//ゴールの近くにボールをセット
					Ball->setPosition(900, 50);
				}
				else
				{
					Ball->setPosition(10, DisplaySize.height / 2);
				}

				BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);
				BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
				BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
				BallPhysic->setContactTestBitmask(INT_MAX);

				//衝突判定するために識別子を格納する
				Ball->setPhysicsBody(BallPhysic);
				this->addChild(Ball);
				Ball->setTag(static_cast<int>(PhysicName::Ball));
			}
			else
			{
				//ボールが画面外に行ったとき
				if (Ball->getPositionY()<0 || Ball->getPositionY()>DisplaySize.height || Ball->getPositionX()<0 || Ball->getPositionX()>DisplaySize.width)
				{
					Ball->removeFromParent();
					//ボールの位置を最初の位置に戻す
					Ball = Sprite::create("images/ball.png");

					if (BossCnt>3)
					{
						Ball->setPosition(900, 50);
					}
					else
					{
						Ball->setPosition(10, DisplaySize.height / 2);
					}

					BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);
					BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
					BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
					BallPhysic->setContactTestBitmask(INT_MAX);
					Ball->setPhysicsBody(BallPhysic);
					this->addChild(Ball);

					//自分自身にタグ付けする
					Ball->setTag(static_cast<int>(PhysicName::Ball));
				}
				//ボールの範囲取得
				BallRect = Ball->getBoundingBox();
			}
		}
	}
	//時間を1秒ずつ減らす
	dtime -= dt;

	//ゲーム開始時間になったら
	if (dtime<0)
	{
		//他の処理も動かすためにフラグを変更
		delayflg = true;

		//制限時間
		time -= dt;
		timelbl->setString(StringUtils::toString((int)time) + "秒");

		//ゲームオーバー
		if (time<0)
		{
			trans = TransitionFade::create(3.0f, GameOverScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}
	}
}
void PlayScene::input()
{
	//タッチイベント
	listener = EventListenerTouchOneByOne::create();
	
	//タッチし始めたとき
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//ゲーム開始まで待つ
		if (delayflg==true)
		{
			//ボールの範囲取得
			BallRect = Ball->getBoundingBox();
			if (scheduleflg == true)
			{
				//タッチした位置とボールの範囲が同じのとき
				if (BallRect.containsPoint(TouchPos = touch->getLocation()))
				{
					//タッチフラグをtrueに
					TouchFlg = true;
					
					//ノードにボールを格納
					BallNode = Ball;
				}
			}
		}
		return true;
	};
	
	//放したとき
	listener->onTouchEnded = [this](Touch *touch, Event *event)
	{
		if (delayflg==true)
		{
			//タッチフラグがtrueのとき
			if (TouchFlg == true)
			{
				//引っ張った分×500の力で飛ばす
				BallPos = (TouchPos - touch->getLocation()) * 500;
				
				//格納したノードに力を加える
				BallNode->getPhysicsBody()->applyImpulse(BallPos);
				
				//タッチフラグ初期化
				TouchFlg = false;
			}
		}
	};
	
	//タッチするかどうかを監視
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//接触時に呼ばれる関数を実装
	contact = EventListenerPhysicsContact::create();
	
	//接触時に呼ばれる
	contact->onContactBegin = [this](PhysicsContact& c)
	{
		auto other = (c.getShapeA()->getBody() == this->getChildByTag(static_cast<int>(PhysicName::Goal))->getPhysicsBody()) ? c.getShapeB() : c.getShapeA();
		
		//接触相手の情報を取得
		auto body = other->getBody();
		
		//識別子を取得
		auto cate = body->getCategoryBitmask();

		//連続で接触させない
		if (contactflg == false)
		{
			//衝突してステージ移行した後の時間と一緒である場合は当たり判定に入らない
			//ステージ移行してからボールが地面に落下するまでの時間(ボスステージのゴール除く)は約1秒かかるので
			//入れさせないことにより連続して進むことを防ぐ
			//ボスのゴールは目の前なので1秒かからないが、そこだけ別にするとまた連続で入り
			//3つ目のフェイクを通った時点でクリアになってしまうため1秒以上開けさせる
			if (ContactTime != (int)time)
			{
				//ゴール(フェイク)とボールが当たったら
				if (cate & static_cast<int>(PhysicName::Ball))
				{
					//接触させないためにフラグ変更
					contactflg = true;

					//ステージの数がステージ最大数を超えているかどうか
					if (StageNum < StageMax)
					{
						//スケジュールを止めるためにフラグを変更
						scheduleflg = false;

						//ボールを一度消す
						Ball->removeFromParent();

						//各PhysicsShapeCacheをもう一度設定する
						StageShape = PhysicsShapeCache::getInstance();
						GoalShape = PhysicsShapeCache::getInstance();
						Fake1Shape = PhysicsShapeCache::getInstance();
						Fake2Shape = PhysicsShapeCache::getInstance();
						Fake3Shape = PhysicsShapeCache::getInstance();

						//ステージ・ゴールを消す
						Stage->removeFromParent();
						Goal->removeFromParent();

						//フェイクも表示していたらフェイクも消す
						if (BossCnt > 0 && (fakeflg == false))
						{
							Fake1->removeFromParent();
							Fake2->removeFromParent();
							Fake3->removeFromParent();
						}

						//ボスステージならフェイク表示用のカウントをする
						if ((StageNum == Boss_Stage) && (fakeflg == false))
						{
							BossCnt++;
						}
						else
						{
							StageNum++;
						}

						//ボスステージを読み込ませるための処理
						if ((StageNum == Boss_Stage) && (BossCnt > 0))
						{
							StageName = "St0" + to_string(StageNum + 1);
						}
						else
						{
							StageName = "St0" + to_string(StageNum);
						}

						//ステージのプロパティリストを読み込む
						StageShape->addShapesWithFile("plist/" + StageName + ".plist");

						//ステージ表示
						{
							Stage = Sprite::create("images/" + StageName + ".png");
							StagePhysic = StageShape->setPhysics(StageName, Stage);
							Stage->setPhysicsBody(StagePhysic);
							Stage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Stage->setPosition(0, 0);
							this->addChild(Stage);
						}

						//ボスステージの時
						if ((StageNum == Boss_Stage) && (BossCnt > 0) && (fakeflg == false))
						{
							//ゴール・フェイクのプロパティリストを読み込む
							GoalShape->addShapesWithFile("plist/" + StageName + "Goal.plist");
							Fake1Shape->addShapesWithFile("plist/" + StageName + "-1.plist");
							Fake2Shape->addShapesWithFile("plist/" + StageName + "-2.plist");
							Fake3Shape->addShapesWithFile("plist/" + StageName + "-3.plist");

							//ゴール・フェイクの表示
							Goal = Sprite::create("images/" + StageName + "Goal.png");
							Fake1 = Sprite::create("images/" + StageName + "-1.png");
							Fake2 = Sprite::create("images/" + StageName + "-2.png");
							Fake3 = Sprite::create("images/" + StageName + "-3.png");

							//最初のフェイク
							if (BossCnt == 1)
							{
								Fake1Physic = GoalShape->setPhysics(StageName + "-1", Fake1);

								//識別子とタグ付け
								Fake1Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake1Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake1->setPhysicsBody(Fake1Physic);
								Fake1Physic->setContactTestBitmask(INT_MAX);
								Fake1->setTag(static_cast<int>(PhysicName::Goal));

							}

							//2番目のフェイク
							else if (BossCnt == 2)
							{
								Fake2Physic = GoalShape->setPhysics(StageName + "-2", Fake2);

								//識別子とタグ付け
								Fake2Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake2Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake2->setPhysicsBody(Fake2Physic);
								Fake2Physic->setContactTestBitmask(INT_MAX);
								Fake2->setTag(static_cast<int>(PhysicName::Goal));
							}

							//3番目のフェイク
							else if (BossCnt == 3)
							{
								Fake3Physic = GoalShape->setPhysics(StageName + "-3", Fake3);

								//識別子とタグ付け
								Fake3Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake3Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake3->setPhysicsBody(Fake3Physic);
								Fake3Physic->setContactTestBitmask(INT_MAX);
								Fake3->setTag(static_cast<int>(PhysicName::Goal));
							}

							//3番目のフェイクまで衝突して進むことによってゴールに到達できる
							else
							{
								GoalPhysic = GoalShape->setPhysics(StageName + "Goal", Goal);

								//識別子とタグ付け
								GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Goal->setPhysicsBody(GoalPhysic);
								GoalPhysic->setContactTestBitmask(INT_MAX);
								Goal->setTag(static_cast<int>(PhysicName::Goal));

								//フェイクは使わないのでフラグを変更
								fakeflg = true;

								//ステージのカウントも進める
								//ゴールに当たった時にクリアシーンに移行させるため
								StageNum++;
							}

							//各スプライトの設定
							Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Goal->setPosition(0, 0);
							Fake1->setPosition(0, 0);
							Fake2->setPosition(0, 0);
							Fake3->setPosition(0, 0);
							this->addChild(Goal);
							this->addChild(Fake1);
							this->addChild(Fake2);
							this->addChild(Fake3);
						}

						//ボスステージ以外
						else
						{
							//ゴールのプロパティリストを読み込む
							GoalShape->addShapesWithFile("plist/" + StageName + "Goal.plist");

							//ゴール表示
							{
								Goal = Sprite::create("images/" + StageName + "Goal.png");
								GoalPhysic = GoalShape->setPhysics(StageName + "Goal", Goal);

								//識別子とタグ付け&表示
								GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								GoalPhysic->setContactTestBitmask(INT_MAX);
								Goal->setPhysicsBody(GoalPhysic);
								Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
								Goal->setPosition(0, 0);
								this->addChild(Goal);
								Goal->setTag(static_cast<int>(PhysicName::Goal));
							}
						}

						//ボールをもう一度作成
						Ball = Sprite::create("images/ball.png");

						//ボスステージがクリアできるとき
						if (BossCnt > 3)
						{
							Ball->setPosition(900, 50);
						}
						else
						{
							Ball->setPosition(10, DisplaySize.height / 2);
						}
						BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);

						//識別子とタグ付け&表示
						BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
						BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
						BallPhysic->setContactTestBitmask(INT_MAX);
						Ball->setPhysicsBody(BallPhysic);
						this->addChild(Ball);
						Ball->setTag(static_cast<int>(PhysicName::Ball));

						//スケジュールのフラグを変更して処理を動かす
						scheduleflg = true;
					}

					//クリアした時
					else
					{
						//ゲームの制限時間からかかった時間を引いてスコアの時間を出す
						int score = Time;
						score = score - (int)time;

						Score sc;

						//スコアを書き込む
						sc.SetScore(score);
						trans = TransitionFade::create(3.0f, GameClearScene::createScene());
						Director::getInstance()->replaceScene(trans);
						this->unscheduleUpdate();
					}

					//処理が終わったので接触できるようにフラグを変更
					contactflg = false;

					//処理が終わった後に時間を入れる
					ContactTime = (int)time;
				}
			}
			
		}
		return true;
	};
	//接触判定
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);
}
