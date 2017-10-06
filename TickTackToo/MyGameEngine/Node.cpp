/*Node.cpp*/

/*2017-07-13
	��� �B��
		�X�v���C�g�⃉�x���Ȃǂ��܂Ƃ߂�Node�̃v���O����*/

/****�C���N���[�h****/
#include "Node.h"
#include"Scene.h"
/********************/


//�R���X�g���N�^
Node::Node()
{
	//�ϐ��̏�����
	_size = D3DXVECTOR3(0, 0, 0);
	_anchorPoint = D3DXVECTOR3(0.5, 0.5, 0);
	_position = D3DXVECTOR3(0, 0, 0);
	_rotate = D3DXVECTOR3(0, 0, 0);
	_scale = D3DXVECTOR3(1, 1, 1);
	_target = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0, 0, 0);
	_pParent = nullptr;
}

//�f�X�g���N�^
Node::~Node()
{

}

//���z�֐�
void Node::Draw()
{

}

//�m�[�h�̖ʐ�(�l�p�`)���擾
MyRect Node::GetBoundingBox()
{
	//4�̒��_�̍��W���擾

	//2017-10-04
	//�C��
	//�͈͂����ɒ����Ȃ��Ă���
	MyRect rect;
	rect._left = _position.x - _size.x * _anchorPoint.x * _scale.x;
	rect._top = _position.y - _size.y * _anchorPoint.y * _scale.y;
	rect._width = _size.x * _scale.x;
	rect._height = _size.y * _scale.y;

	return rect;
}

//�e�̍폜
void Node::RemoveFromParent()
{
	_pParent->RemoveChild(this);
}

//�A���J�[�|�C���g���Z�b�g
void Node::SetAnchorPoint(float x, float y, float z)
{
	_anchorPoint = D3DXVECTOR3(x, y, z);
}

//�ʒu���Z�b�g
void Node::SetPosition(float x, float y, float z)
{
	_position = D3DXVECTOR3(x, y, z);
}

//��]�p�x���Z�b�g
void Node::SetRotate(float x, float y, float z)
{
	_rotate = D3DXVECTOR3(x, y, z);
}

//�I�[�o�[���[�h
//��]�p�x���Z�b�g(Z���̂�)
void Node::SetRotate(float z)
{
	_rotate = D3DXVECTOR3(0, 0, z);
}

//�g�嗦���Z�b�g
void Node::SetScale(float x, float y, float z)
{
	_scale = D3DXVECTOR3(x, y, z);
}

//���Ă���ꏊ���Z�b�g
void  Node::SetTarget(float x, float y, float z)
{
	_target = D3DXVECTOR3(x, y, z);
}

//�J�����̏���Z�b�g
void  Node::SetUp(float x, float y, float z)
{
	_up = D3DXVECTOR3(x, y, z);
}

//�e���Z�b�g
void Node::SetParent(Scene *pScene)
{
	_pParent = pScene;
}

//�T�C�Y���擾
D3DXVECTOR3 Node::GetSize()
{
	//���ۂɕ\�����Ă���T�C�Y�͉摜�T�C�Y�~�g�嗦
	return D3DXVECTOR3(_size.x * _scale.x, _size.y * _scale.y, _size.z * _scale.z);
}

//�A���J�[�|�C���g���擾
D3DXVECTOR3 Node::GetAnchorPoint()
{
	return _anchorPoint;
}

//�ʒu���擾
D3DXVECTOR3 Node::GetPosition()
{
	return _position;
}

//��]�p�x���擾
D3DXVECTOR3 Node::GetRotate()
{
	return _rotate;
}

//�g�嗦���擾
D3DXVECTOR3 Node::GetScale()
{
	return _scale;
}