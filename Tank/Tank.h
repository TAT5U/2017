/*Tank.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "MyGameEngine\Fbx.h"
/********************/


//Fbx���p��
class Tank : public Fbx
{
	//��]�Ƒ��s�̃X�s�[�h
	const float ROTATE_SPEED;
	const float RUN_SPEED;

	//���������x�������i�[����s��
	D3DXVECTOR3 _move;

	D3DXVECTOR3 _hitWallNormal;

	bool isHit[2];

public:

	//�R���X�g���N�^
	Tank();

	//�f�X�g���N�^
	~Tank();

	//���͏���
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Input();

	//�ǂݍ��ݏ���
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Load();

	//������t���O�̃Z�b�^�[
	void SetHit(bool hitFlg, int element);

	//�Ǎ���p�̃x�N�g���̃Z�b�^�[
	void SetHitNormal(D3DXVECTOR3 normalVal);

	//�}�N��
	CREATE_FUNC(Tank);
};

