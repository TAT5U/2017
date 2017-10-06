/*PlayScene.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
/********************/


//Sceneクラスを継承する
class PlayScene : public Scene
{
	/****************当たり判定****************/
	//スプライトとラベルで当たり判定を行うため
	//メンバ変数を使用する

	//スプライト
	Sprite *_sprite;

	//ラベル
	Label *_label;
	/******************************************/

	//スプライトの有無
	bool _spriteFlg;

	//ポリゴン
	Quad *_quad;

	//回転角度
	int _angle;

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
};