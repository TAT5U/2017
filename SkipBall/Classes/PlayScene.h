/*PlayScene.h*/

#pragma once
#include "cocos2d.h"
#include "PhysicsShapeCache.h"

using namespace std;
USING_NS_CC;

//識別子の定義
enum  class PhysicName
{
	Goal = 1,
	Ball = 2,
};
class PlayScene : public Layer
{
public:
	PlayScene();
	~PlayScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//スプライト ステージ・ボール・ゴール・フェイク
	Sprite *Stage, *Ball, *Goal,*Fake1,*Fake2,*Fake3,*bk;

	//ラベル 制限時間
	Label *timelbl;

	//float型 時間・ゲーム開始時間
	float time,dtime;

	//物理エンジン ボール・ゴール・ステージ・フェイク
	PhysicsBody *BallPhysic,*GoalPhysic,*StagePhysic, *Fake1Physic, *Fake2Physic, *Fake3Physic;

	//PhysicsShapeCacheはプロパティリストに格納されているデータを使って物理エンジンを
	//画像に取り付けてくれるPhysicsShapeCacheクラスにある
	//PhysicsShapeCache ステージ・ゴール・フェイク
	PhysicsShapeCache *StageShape, *GoalShape, *Fake1Shape, *Fake2Shape, *Fake3Shape;

	//オブジェクトの衝突範囲 ボール
	Rect BallRect;

	//位置 クリック時・ボール
	Vec2 TouchPos, BallPos;

	//ノード ボールを飛ばすため
	Node *BallNode;

	//int型 ステージ番号・ボスステージカウント・衝突時の時間
	int StageNum,BossCnt,ContactTime;

	//string型 ステージ名
	string StageName;

	//bool型 フラグ
	bool fakeflg, scheduleflg,contactflg, TouchFlg, delayflg;

	//マウスイベント
	EventListenerTouchOneByOne *listener;
	EventListenerPhysicsContact *physicsContact;

	//当たり判定イベント
	EventListenerPhysicsContact *contact;

	//シーン移行
	TransitionFade *trans;

	//ウィンドウサイズ
	Size DisplaySize;

	static Scene* createScene();
	CREATE_FUNC(PlayScene);
};