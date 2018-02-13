/*Tank.cpp*/

/*2017-10-19
	��� �B��
		��ԗp�v���O����*/

/****�C���N���[�h****/
#include "Tank.h"
/********************/


//�R���X�g���N�^
//const�Ő錾�����ϐ��ɒl��ݒ肷��ꍇ�͈ȉ��̂悤�ɂ���
Tank::Tank()
 : ROTATE_SPEED(5.0f), RUN_SPEED(0.30f)
{
	//�ϐ��̏�����
	_move = D3DXVECTOR3(0, 0, 0);
}


//�f�X�g���N�^
Tank::~Tank()
{
}


//�ǂݍ��ݏ���
void Tank::Load()
{
	//��ԓǂݍ���
	Fbx::Load("Assets//Tank.fbx");
}


//���͏���
void Tank::Input()
{
	//�E�ƍ��̉�]
	if (g.pInput->IsKeyPush(DIK_D))
	{
		_rotate.y += ROTATE_SPEED;
	}
	else if (g.pInput->IsKeyPush(DIK_A))
	{
		_rotate.y -= ROTATE_SPEED;
	}

	//�O�i
	if (g.pInput->IsKeyPush(DIK_W))
	{
		_move = D3DXVECTOR3(0, 0, RUN_SPEED);

		//��Ԃ̊p�x�����킹���i�ݕ���������
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(_rotate.y));
		D3DXVec3TransformCoord(&_move, &_move, &mat);

		//�������Ă���Ƃ��͕Ǎ���
		//�{���̓Q�b�^�[������Ȃ���΂Ȃ�Ȃ�
		if (isHit[0] == false)
		{

			_position += _move;
		}
		else
		{
			_position += _move - D3DXVec3Dot(&_move, &_hitWallNormal) * _hitWallNormal;
		}
	}
	else if (g.pInput->IsKeyPush(DIK_S))
	{
		_move = D3DXVECTOR3(0, 0, -RUN_SPEED);

		//��Ԃ̊p�x�����킹���i�ݕ���������
		D3DXMATRIX mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(_rotate.y));
		D3DXVec3TransformCoord(&_move, &_move, &mat);

		//�������Ă���Ƃ��͕Ǎ���
		//�{���̓Q�b�^�[������Ȃ���΂Ȃ�Ȃ�
		if (isHit[1] == false)
		{

			_position += _move;
		}
		else
		{
			_position += _move - D3DXVec3Dot(&_move, &_hitWallNormal) * _hitWallNormal;
		}
	}
}

//������t���O�̃Z�b�^�[
void Tank::SetHit(bool hitFlg, int element)
{
	isHit[element] = hitFlg;
}

//�Ǎ���p�̃x�N�g���̃Z�b�^�[
void Tank::SetHitNormal(D3DXVECTOR3 normalVal)
{
	_hitWallNormal = normalVal;
}