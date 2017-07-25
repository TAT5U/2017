/*RankScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class RankScene : public Layer
{
public:
	RankScene();
	~RankScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//クリックした時
	void ClickBack(Ref *pSender);

	//マイスコア・ランク・バックラベル
	Label *myScore, *rank, *rankScore,*back;

	//Sprite変数 バックグラウンド・ラベル下地・カーソル・select
	Sprite *backGround, *labelFD, *cursor, *select, *select2;

	//backラベルとカーソルの衝突
	Rect backRect, cursorRect;

	//selectの表示フラグ
	bool selectflg;

	//バックをボタン化
	MenuItemLabel *backButton;
	Menu *backMenu;

	//要素数・カウント
	int n,i;

	//スコア格納用
	std::string str,str2,s,maxScore;

	//マウスイベント
	EventListenerMouse *mouseListner;

	//マウスカーソルイベント
	EventMouse *mouse;

	//ウィンドウサイズ
	Size DisplaySize;

	//シーン移行用
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(RankScene);
};