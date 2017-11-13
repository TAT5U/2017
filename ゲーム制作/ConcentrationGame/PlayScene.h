/*PlayScene.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "Player.h"
#include "BackGround.h"
#include "Trump.h"
#include "Judge.h"
/********************************/


class PlayScene : public Scene
{
	//背景
	BackGround *backGround;

	//トランプ(表と裏)
	Trump **trump[2];

	//プレイヤー
	Player **player;

	//判定
	Judge *judge;

	//終了・リトライ
	Sprite *end, *retry;

	//ターンラベル
	Label *turnLabel;

	//ターン表示用テキスト
	TCHAR turnText[32];

	//ループ用カウント・ゲームカウント
	int count, gameCount;

	//ターン
	int turn;

	//クリックしたところの要素格納用変数
	int clickNumber[2], clickCount;

	//クリックされているかどうか
	bool handleOpenFlg;

	//ゲーム中かどうか
	bool gamePlayFlg;

	//フェードフラグ
	bool fadeFlg;

public:

	PlayScene();
	~PlayScene();

	void Init() override;
	void Update() override;
	void Input() override;

	//リトライかExitが押されたとき
	void RetryORExit();

	//Judge呼び出し
	bool CallJudgement();

	//盤面の監視
	void BoardMonitor();

	//ターン変更
	void ChangeTurn();

	//トランプのクリック時
	void OnClick();



};