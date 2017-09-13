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
	_parent = nullptr;
}

//�f�X�g���N�^
Node::~Node()
{

}

//�m�[�h�̖ʐ�(�l�p�`)���擾
MyRect Node::GetBoundingBox()
{
	//4�̒��_�̍��W���擾
	MyRect rect;
	rect._left = _position.x - _size.x * _anchorPoint.x * _scale.x;
	rect._top = _position.y - _size.y * _anchorPoint.y * _scale.y;
	rect._width = _size.x * _scale.x + rect._left;
	rect._height = _size.y * _scale.y + rect._top;

	return rect;
}

//
void Node::RemoveFromParent()
{
	_parent->RemoveChild(this);
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

//�e���Z�b�g
void Node::SetParent(Scene *pScene)
{
	_parent = pScene;
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