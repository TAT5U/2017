#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlayScene;
class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//クリックした時(GameOver)
	void ClickGameOver(Ref *pSender);

	//クリックした時(Score)
	void ClickScore(Ref *pSender);

	//ゲームオーバー・スコアラベル
	Label *gameOver,*score;

	Sprite *backGround, *labelFD,*labelFD2,*cursor, *select, *select2,*select3, *select4;

	Rect scoreRect,gameOverRect,cursorRect;

	bool selectflg,selectflg2;

	//ゲームオーバー・スコアをボタン化
	MenuItemLabel *gameOverButton,*scoreButton;
	Menu *gameOverMenu,*scoreMenu;

	//マウスイベント
	EventListenerMouse *mouseListner;

	//マウスカーソルイベント
	EventMouse *mouse;

	//ウィンドウサイズ
	Size DisplaySize;

	//シーン移行用
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
};