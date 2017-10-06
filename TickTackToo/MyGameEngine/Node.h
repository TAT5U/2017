/*Node.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Global.h"
/********************/


//前方宣言
class Scene;

//ラベルやスプライトをノードにまとめるためのノードクラス
class Node
{
protected:
	
	//サイズ
	D3DXVECTOR3 _size;

	//アンカーポイント
	D3DXVECTOR3 _anchorPoint;

	//位置
	D3DXVECTOR3 _position;

	//回転角度	3Dプログラム用	2Dならfloat型
	D3DXVECTOR3 _rotate;

	//拡大率
	D3DXVECTOR3 _scale;

	//見ている場所
	D3DXVECTOR3 _target;

	//カメラの上
	D3DXVECTOR3 _up;

	//親を入れる変数
	Scene *_pParent;

public:

	//コンストラクタ
	Node();

	//デストラクタ
	//継承されるデストラクタ
	virtual ~Node();

	/********************何もしない仮想関数********************/
	//今までは純粋仮想関数にして0を格納していたが
	//Nodeを継承したカメラを使用できるようにするためには
	//何もしない仮想関数に変更しないといけない
	//引数->なし
	//戻値->なし
	virtual void Draw();
	/****************************************************/


	//ノードの面積(四角形)を取得
	//当たり判定で使用
	//引数->なし
	//戻値->Rect(4つの頂点)
	MyRect GetBoundingBox();

	//親の削除
	void RemoveFromParent();

	/**********************セッター**********************/
	//デフォルトの値を格納することによって
	//値を入れる時に省略できる
	//戻値->なし

	//アンカーポイントをセット
	//引数->左・上・奥
	void SetAnchorPoint(float x, float y, float z = 0);

	//位置をセット
	//引数->左・上・奥
	void SetPosition(float x, float y, float z = 0);

	//回転角度をセット
	//引数->角度(3つ	3Dの時に使用する)
	void SetRotate(float x, float y, float z);

	//オーバーロード
	//回転角度をセット(Z軸のみ)
	//引数->角度
	void SetRotate(float z);

	//拡大率をセット
	//引数->縦・横・奥
	void SetScale(float x, float y, float z = 1);

	//見ている場所をセット
	void SetTarget(float x, float y, float z);

	//カメラの上をセット
	void SetUp(float x, float y, float z);

	//親をセット
	void SetParent(Scene *pScene);
	/****************************************************/


	/**********************ゲッター**********************/
	//引数->なし
	//戻値->なし

	//サイズを取得
	D3DXVECTOR3 GetSize();

	//アンカーポイントを取得
	D3DXVECTOR3 GetAnchorPoint();

	//位置を取得
	D3DXVECTOR3 GetPosition();

	//回転角度を取得
	D3DXVECTOR3 GetRotate();

	//拡大率を取得
	D3DXVECTOR3 GetScale();
	/****************************************************/
};