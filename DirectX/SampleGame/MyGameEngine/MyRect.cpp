/*MyRect.cpp*/

/*2017-06-07
	狩野 達哉
		cocos2dxのようなRectの使い方
			をするためのオリジナルのRectプログラム*/

/****インクルード****/
#include "MyRect.h"
/********************/


//コンストラクタ
MyRect::MyRect()
{
	//変数の初期化
	_left = 0;
	_top = 0;
	_width = 0;
	_height = 0;
}

//引数付きコンストラクタ
MyRect::MyRect(float left, float top, float width, float height)
{
	//メンバ変数に格納
	_left = left;
	_top = top;
	_width = width;
	_height = height;
}

//デストラクタ
MyRect::~MyRect()
{

}

//当たり判定
//ノードとノード
bool MyRect::IntersectsRect(MyRect targetRect)
{
	//4つの頂点で判定する
	if ((targetRect._left<_width&&targetRect._width>_left)&&(targetRect._top<_height&&targetRect._height>_top))
	{
		return true;
	}
	return false;
}

//当たり判定
//ノードと点
bool MyRect::ContainsPoint(D3DXVECTOR3 targetPos)
{
	//4つの頂点と座標で判定する
	if (_left + _width > targetPos.x&&_left < targetPos.x&&_top + _height >targetPos.y&&_top < targetPos.y)
	{
		return true;
	}
	return false;
}