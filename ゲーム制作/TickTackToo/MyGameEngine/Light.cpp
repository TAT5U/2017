/*Light.cpp*/

/*2017-09-18
	��� �B��
		���C�g���g�p�ł���悤�ɂ���Light�v���O����*/

/****�C���N���[�h****/
#include "Light.h"
/********************/


//�f�X�g���N�^
Light::~Light()
{
}

//�ÓI�֐�	���C�g�̍쐬
Light *Light::Create()
{
	//���C�g�̏��
	D3DLIGHT9 lightState;

	//���C�g�̏������ׂď�����
	ZeroMemory(&lightState, sizeof(lightState));

	//���C�g�̎�ނ𕽍s�����ɐݒ�
	lightState.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̌������E���������ɐݒ�
	lightState.Direction = D3DXVECTOR3(1, -1, 1);

	//���C�g�̐F��ݒ�
	lightState.Diffuse.r = 1.0f;
	lightState.Diffuse.g = 1.0f;
	lightState.Diffuse.b = 1.0f;

	//���C�g���Z�b�g
	//�������̓��C�g�̔ԍ�
	g.pDevice->SetLight(0, &lightState);

	//���C�g��L����
	g.pDevice->LightEnable(0, true);

	Light *pLight = new Light;
	return pLight;
}
