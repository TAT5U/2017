/*TitleScene.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
#include "MyGameEngine\Fade.h"
#include "PlayScene.h"
/********************/


//Sceneクラスを継承する
class TitleScene : public Scene
{
	Sprite *backGround;
	Sprite *title;
	Sprite *start;

	int alpha;
	bool fadeFlg;
	bool isFadeFlg;

public:

	//コンストラクタ
	TitleScene();

	//デストラクタ
	~TitleScene();

	/********************純粋仮想関数********************/
	//純粋仮想関数を複数使用するのでオーバーロードする
	//オーバーロードしない場合、エラーを吐く
	//引数->なし
	//戻値->なし
	void Init() override;
	void Update() override;
	void Input() override;
	/****************************************************/;
};