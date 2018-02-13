#pragma once
#include "Node.h"

class Camera : public Node
{
	D3DXVECTOR3 _target;
	D3DXVECTOR3 _up;
	float _angle;
	float _aspect;
	float _nearClip;
	float _farClip;

	D3DXMATRIX _view;
	D3DXMATRIX _proj;
	D3DXMATRIX _billboard;

public:
	Camera();
	~Camera();
	static Camera* Create();
	void Update();


	void SetTarget(D3DXVECTOR3 target){ _target = target; }
	void SetUp(D3DXVECTOR3 up){ _up = up; }
	D3DXMATRIX GetBillboard(){ return _billboard; }
};