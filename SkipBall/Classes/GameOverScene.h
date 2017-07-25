/*GameOverScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//スプライト 背景・ゲームオーバー
	Sprite *bk, *gameOver;

	//ウィンドウサイズ
	Size DisplaySize;

	//マウスイベント
	EventListenerTouchOneByOne *listener;

	//シーン移行
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
};