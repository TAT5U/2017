/*Camera.cpp*/

/*2017-09-13
	��� �B��
		3DCG��\�����鎞�Ɏg�p����Camera�v���O����*/

#include "Camera.h"


Camera::Camera()
{
	// �ϐ��̏�����

	// �P�ʍs��
	// ���������鎞�ȂǂɎg�p����
	D3DXMatrixIdentity(&_view);
}


Camera::~Camera()
{
}

Camera *Camera::Create()
{
	Camera *pCamera = new Camera();
	return pCamera;
}

void Camera::Update()
{

}