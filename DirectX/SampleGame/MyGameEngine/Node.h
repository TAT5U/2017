/*Node.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Global.h"
/********************/

class Scene;

//���x����X�v���C�g���m�[�h�ɂ܂Ƃ߂邽�߂̃m�[�h�N���X
class Node
{
protected:
	
	//�T�C�Y
	D3DXVECTOR3 _size;

	//�A���J�[�|�C���g
	D3DXVECTOR3 _anchorPoint;

	//�ʒu
	D3DXVECTOR3 _position;

	//��]�p�x	3D�v���O�����p	2D�Ȃ�float�^
	D3DXVECTOR3 _rotate;

	//�g�嗦
	D3DXVECTOR3 _scale;

	//�e������ϐ�
	Scene *_parent;

public:

	//�R���X�g���N�^
	Node();

	//�f�X�g���N�^
	//�p�������f�X�g���N�^
	virtual ~Node();

	/********************�������z�֐�********************/
	//�������z�֐��͍ŏ���0���i�[���Ă���
	//�i�[���Ȃ��Ŏ��s���Ă��܂��ƃG���[��f���Ă��܂�
	//�e�V�[���ɂ���ď������Ⴄ���߈ꏏ�ɂł��Ȃ�
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	virtual void Draw() = 0;
	/****************************************************/


	//�m�[�h�̖ʐ�(�l�p�`)���擾
	//�����蔻��Ŏg�p
	//����->�Ȃ�
	//�ߒl->Rect(4�̒��_)
	MyRect GetBoundingBox();

	//
	void RemoveFromParent();

	/**********************�Z�b�^�[**********************/
	//�f�t�H���g�̒l���i�[���邱�Ƃɂ����
	//�l�����鎞�ɏȗ��ł���
	//�ߒl->�Ȃ�

	//�A���J�[�|�C���g���Z�b�g
	//����->���E��E��
	void SetAnchorPoint(float x, float y, float z = 0);

	//�ʒu���Z�b�g
	//����->���E��E��
	void SetPosition(float x, float y, float z = 0);

	//��]�p�x���Z�b�g
	//����->�p�x(3��	3D�̎��Ɏg�p����)
	void SetRotate(float x, float y, float z);

	//�I�[�o�[���[�h
	//��]�p�x���Z�b�g(Z���̂�)
	//����->�p�x
	void SetRotate(float z);

	//�g�嗦���Z�b�g
	//����->�c�E���E��
	void SetScale(float x, float y, float z = 1);

	//�e���Z�b�g
	void SetParent(Scene *pScene);
	/****************************************************/


	/**********************�Q�b�^�[**********************/
	//����->�Ȃ�
	//�ߒl->�Ȃ�

	//�T�C�Y���擾
	D3DXVECTOR3 GetSize();

	//�A���J�[�|�C���g���擾
	D3DXVECTOR3 GetAnchorPoint();

	//�ʒu���擾
	D3DXVECTOR3 GetPosition();

	//��]�p�x���擾
	D3DXVECTOR3 GetRotate();

	//�g�嗦���擾
	D3DXVECTOR3 GetScale();
	/****************************************************/
};