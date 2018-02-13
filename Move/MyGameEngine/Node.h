#pragma once
#include "Global.h"

#define CREATE_FUNC( className )\
	static className* Create()\
	{\
	className* p = new className; \
	p->Load(); \
	return p; \
	}


class Node
{
protected:
	Scene* _parent;

	D3DXVECTOR3 _size;        //サイズ
	D3DXVECTOR3 _anchorPoint; //アンカーポイント
	D3DXVECTOR3 _position;    //位置
	D3DXVECTOR3 _rotate;      //回転角度
	D3DXVECTOR3 _scale;       //拡大率
	float		_distance;
	bool		_isSort;

public:
	Node();
	virtual ~Node();
	virtual void Draw(){};
	virtual void Input(){};
	virtual void Update(){};


	//各セッター
	void SetAnchorPoint(float x, float y, float z = 0);
	void SetPosition(float x, float y, float z = 0);
	void SetPosition(D3DXVECTOR3 v);
	void SetRotate(float x, float y, float z);
	void SetRotate(float z);
	void SetScale(float x, float y, float z = 1);
	void SetDistance(float d){ _distance = d; }
	void SetIsSort(bool b){ _isSort = b; }

	//各ゲッター
	D3DXVECTOR3 GetSize();
	D3DXVECTOR3 GetAnchorPoint();
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotate();
	D3DXVECTOR3 GetScale();
	float		GetDistance(){ return _distance; }
	bool		GetIsSort(){ return _isSort; }

	MyRect GetBoundingBox();
	void SetParent(Scene* parent);
	void RemoveFromParent();
};
