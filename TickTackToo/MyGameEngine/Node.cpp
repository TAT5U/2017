/*Node.cpp*/

/*2017-07-13
	狩野 達哉
		スプライトやラベルなどをまとめるNodeのプログラム*/

/****インクルード****/
#include "Node.h"
#include"Scene.h"
/********************/


//コンストラクタ
Node::Node()
{
	//変数の初期化
	_size = D3DXVECTOR3(0, 0, 0);
	_anchorPoint = D3DXVECTOR3(0.5, 0.5, 0);
	_position = D3DXVECTOR3(0, 0, 0);
	_rotate = D3DXVECTOR3(0, 0, 0);
	_scale = D3DXVECTOR3(1, 1, 1);
	_target = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0, 0, 0);
	_pParent = nullptr;
}

//デストラクタ
Node::~Node()
{

}

//仮想関数
void Node::Draw()
{

}

//ノードの面積(四角形)を取得
MyRect Node::GetBoundingBox()
{
	//4つの頂点の座標を取得

	//2017-10-04
	//修正
	//範囲が横に長くなっていた
	MyRect rect;
	rect._left = _position.x - _size.x * _anchorPoint.x * _scale.x;
	rect._top = _position.y - _size.y * _anchorPoint.y * _scale.y;
	rect._width = _size.x * _scale.x;
	rect._height = _size.y * _scale.y;

	return rect;
}

//親の削除
void Node::RemoveFromParent()
{
	_pParent->RemoveChild(this);
}

//アンカーポイントをセット
void Node::SetAnchorPoint(float x, float y, float z)
{
	_anchorPoint = D3DXVECTOR3(x, y, z);
}

//位置をセット
void Node::SetPosition(float x, float y, float z)
{
	_position = D3DXVECTOR3(x, y, z);
}

//回転角度をセット
void Node::SetRotate(float x, float y, float z)
{
	_rotate = D3DXVECTOR3(x, y, z);
}

//オーバーロード
//回転角度をセット(Z軸のみ)
void Node::SetRotate(float z)
{
	_rotate = D3DXVECTOR3(0, 0, z);
}

//拡大率をセット
void Node::SetScale(float x, float y, float z)
{
	_scale = D3DXVECTOR3(x, y, z);
}

//見ている場所をセット
void  Node::SetTarget(float x, float y, float z)
{
	_target = D3DXVECTOR3(x, y, z);
}

//カメラの上をセット
void  Node::SetUp(float x, float y, float z)
{
	_up = D3DXVECTOR3(x, y, z);
}

//親をセット
void Node::SetParent(Scene *pScene)
{
	_pParent = pScene;
}

//サイズを取得
D3DXVECTOR3 Node::GetSize()
{
	//実際に表示しているサイズは画像サイズ×拡大率
	return D3DXVECTOR3(_size.x * _scale.x, _size.y * _scale.y, _size.z * _scale.z);
}

//アンカーポイントを取得
D3DXVECTOR3 Node::GetAnchorPoint()
{
	return _anchorPoint;
}

//位置を取得
D3DXVECTOR3 Node::GetPosition()
{
	return _position;
}

//回転角度を取得
D3DXVECTOR3 Node::GetRotate()
{
	return _rotate;
}

//拡大率を取得
D3DXVECTOR3 Node::GetScale()
{
	return _scale;
}