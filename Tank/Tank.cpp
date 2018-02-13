/*Tank.cpp*/

/*2017-10-19
	狩野 達哉
		戦車用プログラム*/

/****インクルード****/
#include "Tank.h"
/********************/


//コンストラクタ
//constで宣言した変数に値を設定する場合は以下のようにする
Tank::Tank()
 : ROTATE_SPEED(5.0f), RUN_SPEED(0.30f)
{
	//変数の初期化
	_move = D3DXVECTOR3(0, 0, 0);
}


//デストラクタ
Tank::~Tank()
{
}


//読み込み処理
void Tank::Load()
{
	//戦車読み込み
	Fbx::Load("Assets//Tank.fbx");
}


//入力処理
void Tank::Input()
{
	//右と左の回転
	if (g.pInput->IsKeyPush(DIK_D))
	{
		_rotate.y += ROTATE_SPEED;
	}
	else if (g.pInput->IsKeyPush(DIK_A))
	{
		_rotate.y -= ROTATE_SPEED;
	}

	//前進
	if (g.pInput->IsKeyPush(DIK_W))
	{
		_move = D3DXVECTOR3(0, 0, RUN_SPEED);

		//戦車の角度を合わせた進み方をさせる
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(_rotate.y));
		D3DXVec3TransformCoord(&_move, &_move, &mat);

		//当たっているときは壁刷り
		//本来はゲッターも入れなければならない
		if (isHit[0] == false)
		{

			_position += _move;
		}
		else
		{
			_position += _move - D3DXVec3Dot(&_move, &_hitWallNormal) * _hitWallNormal;
		}
	}
	else if (g.pInput->IsKeyPush(DIK_S))
	{
		_move = D3DXVECTOR3(0, 0, -RUN_SPEED);

		//戦車の角度を合わせた進み方をさせる
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(_rotate.y));
		D3DXVec3TransformCoord(&_move, &_move, &mat);

		//当たっているときは壁刷り
		//本来はゲッターも入れなければならない
		if (isHit[1] == false)
		{

			_position += _move;
		}
		else
		{
			_position += _move - D3DXVec3Dot(&_move, &_hitWallNormal) * _hitWallNormal;
		}
	}
}

//当たりフラグのセッター
void Tank::SetHit(bool hitFlg, int element)
{
	isHit[element] = hitFlg;
}

//壁刷り用のベクトルのセッター
void Tank::SetHitNormal(D3DXVECTOR3 normalVal)
{
	_hitWallNormal = normalVal;
}