/*Camera.cpp*/

/*2017-09-13
	��� �B��
		3DCG��\�����鎞�Ɏg�p����Camera�v���O����*/

/****�C���N���[�h****/
#include "Camera.h"
/********************/


//�R���X�g���N�^
Camera::Camera()
{
	//�ϐ��̏�����
	_position = D3DXVECTOR3(0, 0, -10);
	_target = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0, 1, 0);
	_angle = 60;
	_aspect = (float)g.WINDOW_WIDTH / (float)g.WINDOW_HEIGHT;
	_nearClip = 0.30f;
	_farClip = 1000.0f;

	//�P�ʍs��
	//���������鎞�ȂǂɎg�p����
	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_proj);
}

//�f�X�g���N�^
Camera::~Camera()
{
}

//�ÓI�֐�	�J�����̍쐬
Camera *Camera::Create()
{
	Camera *pCamera = new Camera();
	return pCamera;
}

//�X�V����
void Camera::Update()
{
	//�r���[�s��쐬
	D3DXMatrixLookAtLH(&_view, &_position, &_target, &_up);

	//�r���[�s��ݒ�
	g.pDevice->SetTransform(D3DTS_VIEW, &_view);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixPerspectiveFovLH(&_proj, D3DXToRadian(_angle), _aspect, _nearClip, _farClip);

	//�v���W�F�N�V�����s��ݒ�
	g.pDevice->SetTransform(D3DTS_PROJECTION, &_proj);
}