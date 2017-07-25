/*PlayScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlayScene : public Layer
{
public:
	PlayScene();
	~PlayScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//落下速度
	void FallObj();

	//オブジェクト設定
	void SetObj();

	//レベルアップ時
	void LvUpObj();

	//Sprite変数 オブジェクト・カーソル・バックグラウンド
	Sprite **obj,*cursor,*backGround;

	//位置
	Vec2 *pos,*objpos;

	//要素数・カウントの変数
	int n,i,*flg,score,cnt,*workflg,*spFlg;

	//オブジェクトの衝突範囲
	Rect *objRect, cursorRect;

	//スコア・タイムラベル
	Label *scoreText,*startTimeText;

	//フラグ
	bool speedFlg,*spobjFlg,timeFlg,textTimeFlg;

	//開始時間
	float startTime,startTextTime;

	//マウスイベント
	EventListenerMouse *mouseListner;

	//マウスカーソルイベント
	EventMouse *mouse;

	//アニメーション・シーケンス
	Sprite *anime;
	Animation *anim;
	Animate *animate;
	RemoveSelf *remove;
	Sequence *action;

	//ウィンドウサイズ
	Size DisplaySize;

	static Scene* createScene();
	CREATE_FUNC(PlayScene);
};