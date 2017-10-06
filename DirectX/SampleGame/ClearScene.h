/*ClearScene.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Scene.h"
/********************/


//Sceneクラスを継承する
class ClearScene : public Scene
{
public:

	//コンストラクタ
	ClearScene();

	//デストラクタ
	~ClearScene();

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