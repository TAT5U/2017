#include "Camera.h"


Camera::Camera()
{
	_position = D3DXVECTOR3(0,3, -5);
	_target = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0, 1, 0);

	_angle = 60;
	_aspect = (float)g.WINDOW_WIDTH / g.WINDOW_HEIGHT;
	_nearClip = 2.0f;
	_farClip = 20.0f;


	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_proj);
}


Camera::~Camera()
{
}


Camera* Camera::Create()
{
	Camera* pCamera = new Camera();
	return pCamera;
}

void Camera::Update()
{
	D3DXMatrixLookAtLH(&_view, &_position, &_target, &_up);
	g.pDevice->SetTransform(D3DTS_VIEW, &_view);

	D3DXMatrixPerspectiveFovLH(&_proj, D3DXToRadian(_angle), _aspect, _nearClip, _farClip);
	g.pDevice->SetTransform(D3DTS_PROJECTION, &_proj);

	D3DXMatrixLookAtLH(
		&_billboard,
		&D3DXVECTOR3(0, 0, 0),
		&(_target - _position),
		&_up
		);
	D3DXMatrixInverse(&_billboard, NULL, &_billboard);
}