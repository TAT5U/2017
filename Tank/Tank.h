/*Tank.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "MyGameEngine\Fbx.h"
/********************/


//Fbxを継承
class Tank : public Fbx
{
	//回転と走行のスピード
	const float ROTATE_SPEED;
	const float RUN_SPEED;

	//動かした度合いを格納する行列
	D3DXVECTOR3 _move;

	D3DXVECTOR3 _hitWallNormal;

	bool isHit[2];

public:

	//コンストラクタ
	Tank();

	//デストラクタ
	~Tank();

	//入力処理
	//引数->なし
	//戻値->なし
	void Input();

	//読み込み処理
	//引数->なし
	//戻値->なし
	void Load();

	//当たりフラグのセッター
	void SetHit(bool hitFlg, int element);

	//壁刷り用のベクトルのセッター
	void SetHitNormal(D3DXVECTOR3 normalVal);

	//マクロ
	CREATE_FUNC(Tank);
};

