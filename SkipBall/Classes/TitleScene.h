/*TitleScene*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TitleScene : public Layer
{
public:
	TitleScene();
	~TitleScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//スプライト 背景・タイトル
	Sprite *bk,*title;

	//ラベル スコア
	Label *scorelbl;

	//ウィンドウサイズ
	Size DisplaySize;

	//マウスイベント
	EventListenerTouchOneByOne *listener;

	//シーン移行
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(TitleScene);
};