/*GameClearScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameClearScene : public Layer
{
public:
	GameClearScene();
	~GameClearScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//スプライト 背景・ゲームクリア
	Sprite *bk, *gameClear;

	//ラベル スコア、・新記録
	Label *scorelbl,*newRecordlbl;

	//ウィンドウサイズ
	Size DisplaySize;

	//マウスイベント
	EventListenerTouchOneByOne *listener;

	//シーン移行
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(GameClearScene);
};