/*Fbx.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Node.h"
#include <fbxsdk.h>
/********************/


/**************リンカ**************/
#pragma comment(lib, "libfbxsdk-mt.lib")
/**********************************/


//レイキャスト構造体
struct RayCastData
{
	//発射位置
	D3DXVECTOR3 start;

	//発射方向
	D3DXVECTOR3 dir;

	//当たりかどうか
	bool hit;

	//距離
	float dist;

	//法線
	D3DXVECTOR3 normal;
};


//Fbxを使用するためのクラス
//Nodeを継承
//Quadクラスと似ている
class Fbx : public Node
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

		D3DXVECTOR3 tangent;
	};

	// エフェクト(シェーダー)
	LPD3DXEFFECT _shader;

	//マネージャ
	FbxManager *_manager;

	//インポータ
	FbxImporter *_importer;

	//シーン
	FbxScene *_scene;

	//頂点バッファ
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;

	struct MaterialData
	{
		//インデックスバッファ
		LPDIRECT3DINDEXBUFFER9 indexBuffer;

		//マテリアル
		D3DMATERIAL9 material;

		//テクスチャ
		LPDIRECT3DTEXTURE9 texture;

		//ノーマルテクスチャ
		LPDIRECT3DTEXTURE9 normalTexture;

		//マテリアルごとのポリゴン数
		int polygonCountOfMaterial;

		int shaderPass;

	}*_materialData;

	//ループ用・ループ用2・ループ用3・ノードカウント・バッファカウント・ポリゴンカウント・インデックスカウント・マテリアルカウント
	int initialize, initialize2, initialize3, nodeCount, vertexCount, polygonCount, indexCount, materialCount;

public:

	//コンストラクタ
	Fbx();

	//デストラクタ
	~Fbx();

	//静的関数	Fbxの作成
	//引数->Fbx名
	//戻値->Fbx
	static Fbx *Create(LPCSTR fileName);

	//Fbxの準備
	//引数->Fbx
	//戻値->なし
	void Load(LPCSTR fileName);

	//描画処理
	//引数->なし
	//戻値->なし
	void Draw();

	//入力処理
	//引数->なし
	//戻値->なし
	void Input(){};

	//レイキャストの当たり判定
	void RayCast(RayCastData *data);

	//ノードの内容チェック
	//引数->ノード(ルートノードの子)
	//戻値->なし
	void CheckNode(FbxNode *pNode);

	//メッシュノード処理
	//引数->ノード(子)
	//戻値->なし
	void CheckMesh(FbxMesh *pMesh);

	D3DXVECTOR3 CreateTangent(D3DXVECTOR3 *pos0, D3DXVECTOR3 *pos1, D3DXVECTOR3 *pos2,
		D3DXVECTOR2 *uv0, D3DXVECTOR2 *uv1, D3DXVECTOR2 *uv2);

	void SetShafer(LPD3DXEFFECT setShader);
};