#include "Node.h"
#include "Scene.h"

Node::Node()
{
	_parent = nullptr;

	_anchorPoint = D3DXVECTOR3(0.5, 0.5, 0);
	_position = D3DXVECTOR3(0, 0, 0);
	_rotate = D3DXVECTOR3(0, 0, 0);
	_scale = D3DXVECTOR3(1, 1, 1);
	_size = D3DXVECTOR3(0, 0, 0);

	_isSort = false;
}


Node::~Node()
{
}


MyRect Node::GetBoundingBox()
{
	MyRect rect;

	rect._left = _position.x - GetSize().x * _anchorPoint.x ;
	rect._top = _position.y - GetSize().y * _anchorPoint.y;
	rect._width = GetSize().x;
	rect._height = GetSize().y;

	return rect;
}

//////////////////////////ここからアクセス関数/////////////////////////////////////

//アンカーポイントをセット
void Node::SetAnchorPoint(float x, float y, float z)
{
	_anchorPoint.x = x;
	_anchorPoint.y = y;
	_anchorPoint.z = z;
}

//位置をセット
void Node::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}
void Node::SetPosition(D3DXVECTOR3 v)
{
	_position = v;
}


//回転角度をセット
void Node::SetRotate(float x, float y, float z)
{
	_rotate.x = x;
	_rotate.y = y;
	_rotate.z = z;
}

//回転角度をセット(Ｚ軸のみ）
void Node::SetRotate(float z)
{
	_rotate.x = 0;
	_rotate.y = 0;
	_rotate.z = z;
}

//拡大率をセット
void Node::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}





//サイズを取得
D3DXVECTOR3 Node::GetSize()
{
	D3DXVECTOR3 size;
	size.x = _size.x * _scale.x;
	size.y = _size.y * _scale.y;
	size.z = _size.z * _scale.z;
	return size;
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


void Node::SetParent(Scene* parent)
{
	_parent = parent;
}

void Node::RemoveFromParent()
{
	_parent->RemoveChild(this);
}