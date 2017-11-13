/*Quad.cpp*/

/*2017-09-18
	狩野 達哉
		ポリゴンを作成し表示するQuadプログラム*/

/****インクルード****/
#include "Quad.h"
/********************/


//コンストラクタ
Quad::Quad()
{
	//変数の初期化
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;
	_pTexture = nullptr;
}

//デストラクタ
Quad::~Quad()
{
	//解放処理
	SAFE_RELEASE(_pTexture);
	SAFE_RELEASE(_pIndexBuffer);
	SAFE_RELEASE(_pVertexBuffer);
}

//静的関数	ポリゴンの作成
Quad *Quad::Create(LPCSTR fileName)
{
	Quad *pQuad = new Quad;
	pQuad->Load(fileName);
	return pQuad;
}

//ポリゴンの準備
void Quad::Load(LPCSTR fileName)
{
	//頂点を設定
	//法線は全部手前
	Vertex vertexList[] = { D3DXVECTOR3(-1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 0), 
							D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0), 
							D3DXVECTOR3(1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 1), 
							D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1) };

	//バッファを確保
	g.pDevice->CreateVertexBuffer(sizeof(vertexList), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_pVertexBuffer, 0);

	//バッファをロック
	//データをコピーするにはロックしないといけない
	Vertex *pVCopy;
	_pVertexBuffer->Lock(0, 0, (void**)&pVCopy, 0);

	//データをコピー
	memcpy(pVCopy, vertexList, sizeof(vertexList));

	//コピーが終わったらロックを外す
	_pVertexBuffer->Unlock();

	//インデックス情報
	//DirectXのポリゴンは三角形しか使えないので
	//三角形を使って表示するため、どの頂点を使うか指定する
	//時計回りに指定する
	int indexList[] = { 0, 2, 3, 0, 1, 2 };

	//インデックスバッファを確保
	g.pDevice->CreateIndexBuffer(sizeof(indexList), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_pIndexBuffer, 0);

	//インデックスバッファをロック
	DWORD *pICopy;
	_pIndexBuffer->Lock(0, 0, (void**)&pICopy, 0);

	//データをコピー
	memcpy(pICopy, indexList, sizeof(indexList));

	//コピーが終わったらロックを外す
	_pIndexBuffer->Unlock();

	//マテリアルをすべて初期化
	ZeroMemory(&_material, sizeof(D3DMATERIAL9));

	//マテリアルの色を設定
	//それぞれの色を数値分跳ね返す
	_material.Diffuse.r = 1.0f;
	_material.Diffuse.g = 1.0f;
	_material.Diffuse.b = 1.0f;

	//テクスチャオブジェクトの作成
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);
}

//描画処理
void Quad::Draw()
{
	//頂点バッファをセット
	g.pDevice->SetStreamSource(0, _pVertexBuffer, 0, sizeof(Vertex));

	//インデックスバッファをセット
	g.pDevice->SetIndices(_pIndexBuffer);

	//マテリアルをセット
	g.pDevice->SetMaterial(&_material);

	//テクスチャをセット
	g.pDevice->SetTexture(0, _pTexture);

	//何の情報なのか
	//位置と法線とUV座標
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	//移動行列
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//回転行列
	D3DXMATRIX rotateX, rotateY, rotateZ;
	D3DXMatrixRotationX(&rotateX, D3DXToRadian(_rotate.x));
	D3DXMatrixRotationY(&rotateY, D3DXToRadian(_rotate.y));
	D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(_rotate.z));

	//拡大縮小
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, _scale.z);

	//ワールド行列
	//Unityを参考にした回転の順番
	D3DXMATRIX world = scale * rotateZ * rotateX * rotateY * trans;

	//ワールド行列をセット
	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	//ポリゴンを描画
	//4は頂点数
	//2はポリゴン数(三角形の数)
	g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}