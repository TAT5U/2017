/*Quad.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include"Node.h"
/********************/

class Camera;

//ポリゴンを使用するためのクラス
//Nodeクラスを継承
class Quad : public Node
{
	//頂点の情報
	struct Vertex
	{
		//位置
		D3DXVECTOR3 pos;

		//法線
		D3DXVECTOR3 normal;

		//UV座標
		D3DXVECTOR2 uv;
	};

	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;

	//インデックスバッファ
	LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

	//マテリアル
	D3DMATERIAL9 _material;

	//テクスチャ
	LPDIRECT3DTEXTURE9 _pTexture;

	Camera* _camera;

public:

	//コンストラクタ
	Quad();

	//デストラクタ
	~Quad();

	//静的関数	ポリゴンの作成
	//ポリゴンにテクスチャを貼る
	//引数->画像名
	//戻値->ポリゴン
	static Quad *Create(LPCSTR fileName);

	//ポリゴンの準備
	//引数->画像名
	//戻値->なし
	void Load(LPCSTR fileName);

	//描画処理
	//引数->なし
	//戻値->なし
	void Draw();

	//カメラをセット
	void SetCamera(Camera* camera);
};

