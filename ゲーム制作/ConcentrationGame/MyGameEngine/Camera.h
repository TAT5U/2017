/*Camera.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include"Node.h"
/********************/


//�J�������g�p���邽�߂̃N���X
//Node�N���X���p��
class Camera : public Node
{
	D3DXVECTOR3 _target;
	D3DXVECTOR3 _up;

	//�r���[�s��
	D3DXMATRIX _view;

	//�v���W�F�N�V�����s��
	D3DXMATRIX _proj;

	//����p
	float _angle;

	//�A�X�y�N�g��
	float _aspect;

	//�ŋߋ���
	float _nearClip;

	//�ŉ�����
	float _farClip;

	D3DXMATRIX _billboard;

public:

	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//�ÓI�֐�	�J�����̍쐬
	//����->�Ȃ�
	//�ߒl->�J����
	static Camera *Create();

	//�X�V����
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Update();

	void SetTarget(D3DXVECTOR3 target);
	void SetUp(D3DXVECTOR3 up);

	D3DXMATRIX GetBillboard();
};

