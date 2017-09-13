/*Camera.h*/

#pragma once

#include"Node.h"
class Camera
{
	// �r���[�s��
	D3DXMATRIX _view;

	D3DXVECTOR3 _target;
	D3DXVECTOR3 _up;
public:
	Camera();
	~Camera();
	static Camera *Create();
	void Update();
};

