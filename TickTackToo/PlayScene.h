/*PlayScene.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
/********************/

enum  FrameState
{
	PLAYER = 1,
	CPU = -1,
	DEFAULT = 0,
};

enum  Judgement
{
	WIN = 1,
	LOSE = 2,
	Draw = 3,
};

//Sceneクラスを継承する
class PlayScene : public Scene
{
	/****************当たり判定****************/
	//スプライトとラベルで当たり判定を行うため
	//メンバ変数を使用する

	//フレーム
	Sprite *frame[3][3];

	Sprite *circle, *cross;
	Sprite *gameMes;
	Sprite *frameBackGround;
	Sprite *frameMes;
	Sprite *retry, *end;
	Sprite *backGround;

	FrameState frameSt[3][3];

	bool turnFlg;
	bool gamePlayFlg;
	bool mesFlg;

	int x, y, playCount;

	float waitTime;

public:

	//コンストラクタ
	PlayScene();

	//デストラクタ
	~PlayScene();

	/********************純粋仮想関数********************/
	//純粋仮想関数を複数使用するのでオーバーロードする
	//オーバーロードしない場合、エラーを吐く
	//引数->なし
	//戻値->なし
	void Init() override;
	void Update() override;
	void Input() override;
	/****************************************************/

	Judgement GetJudge();
	void SimpleAI(int i);
};