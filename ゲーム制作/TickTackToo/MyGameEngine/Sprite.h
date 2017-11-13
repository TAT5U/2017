/*Sprite.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include"Global.h"
#include "Node.h"
/********************/


//画像を表示するためのスプライトクラス
//Nodeクラスを継承
class Sprite : public Node
{
	//画像の表示の仕組みはテクスチャに画像を格納し、格納したテクスチャを
	//スプライトに貼り付けて描画する

	//スプライト
	LPD3DXSPRITE _pSprite;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _pTexture, prevTexture;

	//画像の一部を切り出す
	//切抜き範囲
	MyRect _cut;

	RECT cut;

	D3DXVECTOR3 anchor;

	int alpha;

public:

	//コンストラクタ
	Sprite();

	//デストラクタ
	~Sprite();

	//静的関数	画像の作成をcocos2dxのような記述をできるようにする
	//引数->画像名・MyRectの座標
	//戻値->描画するSprite
	static Sprite* Create(LPCSTR fileName, MyRect cut = MyRect(-999, -999, -999, -999));

	//読み込み処理	有り得ない引数を格納しといて切抜き処理の有無を確認する
	//引数->画像名・MyRectの座標
	//戻値->なし
	void Load(LPCSTR fileName,MyRect cut = MyRect(-999, -999, -999, -999));

	//描画処理
	//引数->なし
	//戻値->なし
	void Draw();

	/**********************セッター**********************/
	//デフォルトの値を格納することによって
	//値を入れる時に省略できる
	//切抜き範囲をセット
	//引数->MyRectの範囲
	//戻値->なし
	void SetRect(MyRect cut);
	/****************************************************/

	void SetFadeValue(int val);
};