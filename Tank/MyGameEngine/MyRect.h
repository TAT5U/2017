/*MyRect.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Global.h"
#include "Input.h"
/********************/


//cocos2dxのような範囲指定の書き方をしたり
//小数も使用できるようにするためのオリジナルのRectクラス
class MyRect
{
public:

	//各座標
	float _left;
	float _top;
	float _width;
	float _height;

	//コンストラクタ
	MyRect();

	//これでcocos2dxのように記述できる
	//引数付きコンストラクタ
	//引数->左・上・幅・高さ
	//戻値->なし
	MyRect(float left, float top, float width, float height);

	//デストラクタ
	~MyRect();

	/****************当たり判定****************/

	//ノードとノード
	bool IntersectsRect(MyRect targetRect);

	//ノードと点
	bool ContainsPoint(D3DXVECTOR3 targetPos);
	bool ContainsPoint(Point targetPt);
	/******************************************/
};