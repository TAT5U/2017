/*TitleScene.h*/

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

	//クリックした時
	void ClickStart(Ref *pSender);

	//タイトルラベル
	Label *title,*start;

	//Sprite変数 バックグラウンド・ラベル下地・カーソル・select
	Sprite *backGround,*labelFD,*cursor,*select, *select2;

	//startラベルとカーソルの衝突
	Rect startRect,cursorRect;

	//selectの表示フラグ
	bool selectflg;

	//タイトルをボタン化
	MenuItemLabel *startButton;
	Menu *startMenu;

	//マウスイベント
	EventListenerMouse *mouseListner;

	//マウスカーソルイベント
	EventMouse *mouse;

	//ウィンドウサイズ
	Size DisplaySize;

	//シーン移行用
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(TitleScene);
};