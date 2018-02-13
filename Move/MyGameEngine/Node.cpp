#include "Node.h"
#include "Scene.h"

Node::Node()
{
	_parent = nullptr;

	_anchorPoint = D3DXVECTOR3(0.5, 0.5, 0);
	_position = D3DXVECTOR3(0, 0, 0);
	_rotate = D3DXVECTOR3(0, 0, 0);
	_scale = D3DXVECTOR3(1, 1, 1);
	_size = D3DXVECTOR3(0, 0, 0);

	_isSort = false;
}


Node::~Node()
{
}


MyRect Node::GetBoundingBox()
{
	MyRect rect;

	rect._left = _position.x - GetSize().x * _anchorPoint.x ;
	rect._top = _position.y - GetSize().y * _anchorPoint.y;
	rect._width = GetSize().x;
	rect._height = GetSize().y;

	return rect;
}

//////////////////////////��������A�N�Z�X�֐�/////////////////////////////////////

//�A���J�[�|�C���g���Z�b�g
void Node::SetAnchorPoint(float x, float y, float z)
{
	_anchorPoint.x = x;
	_anchorPoint.y = y;
	_anchorPoint.z = z;
}

//�ʒu���Z�b�g
void Node::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}
void Node::SetPosition(D3DXVECTOR3 v)
{
	_position = v;
}


//��]�p�x���Z�b�g
void Node::SetRotate(float x, float y, float z)
{
	_rotate.x = x;
	_rotate.y = y;
	_rotate.z = z;
}

//��]�p�x���Z�b�g(�y���̂݁j
void Node::SetRotate(float z)
{
	_rotate.x = 0;
	_rotate.y = 0;
	_rotate.z = z;
}

//�g�嗦���Z�b�g
void Node::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}





//�T�C�Y���擾
D3DXVECTOR3 Node::GetSize()
{
	D3DXVECTOR3 size;
	size.x = _size.x * _scale.x;
	size.y = _size.y * _scale.y;
	size.z = _size.z * _scale.z;
	return size;
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


void Node::SetParent(Scene* parent)
{
	_parent = parent;
}

void Node::RemoveFromParent()
{
	_parent->RemoveChild(this);
}