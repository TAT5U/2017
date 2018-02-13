/*PlayScene.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"

#include "ClearScene.h"
/********************/


//前方宣言
class Tank;

//Sceneクラスを継承する
class PlayScene : public Scene
{
	//地面
	Fbx *ground;

	//戦車
	Tank *tank;

	//壁(障害物)
	Fbx *wall;

	//星(アイテム)
	Fbx *star;

	//木
	Quad *tree;

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
	/****************************************************/
};