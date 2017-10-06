/*Camera.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include"Node.h"
/********************/


//カメラを使用するためのクラス
//Nodeクラスを継承
class Camera : public Node
{
	//ビュー行列
	D3DXMATRIX _view;

	//プロジェクション行列
	D3DXMATRIX _proj;

	//視野角
	float _angle;

	//アスペクト比
	float _aspect;

	//最近距離
	float _nearClip;

	//最遠距離
	float _farClip;

public:

	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//静的関数	カメラの作成
	//引数->なし
	//戻値->カメラ
	static Camera *Create();

	//更新処理
	//引数->なし
	//戻値->なし
	void Update();
};

