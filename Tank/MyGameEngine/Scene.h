/*Scene.h*/

//�C���N���[�h�K�[�h
#pragma once

/********�C���N���[�h********/
#include "Global.h"
#include "Sprite.h"
#include "Label.h"
#include "Quad.h"
#include "Light.h"
#include "Fbx.h"

//vector�^���g�p�\�ɂ���
#include <vector>
/****************************/


//std��錾���Ă����ďȗ��ł���悤�ɂ���
using namespace std;

class Camera;

//�e�m�[�h��\�����邽�߂̃V�[���N���X
class Scene
{
	//�m�[�h�̌����J�E���g����ϐ�
	int i;

	//�m�[�h(�X�v���C�g)��ǉ����邽�߂̓��I�z��
	vector<Node *> _pNodes;

protected:
	Camera *_pCamera;

public:

	//�R���X�g���N�^
	Scene();

	//�f�X�g���N�^
	//�p�������f�X�g���N�^
	virtual ~Scene();

	//�m�[�h(�X�v���C�g)��ǉ�
	//����->�`�悷��m�[�h
	//�ߒl->�Ȃ�
	void AddChild(Node *pNode, bool isFade = true);

	//�`�揈��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();

	/********************�������z�֐�********************/
	//�������z�֐��͍ŏ���0���i�[���Ă���
	//�i�[���Ȃ��Ŏ��s���Ă��܂��ƃG���[��f���Ă��܂�
	//�e�V�[���ɂ���ď������Ⴄ���߈ꏏ�ɂł��Ȃ�
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	virtual void Init() = 0;
	virtual void Update();
	virtual void Input();
	/****************************************************/


	//�m�[�h�폜
	void RemoveChild(Node *pNode);

	//�m�[�h�̃\�[�g
	class NodeSort
	{
	public:
		bool operator() (Node * a, Node *b)
		{
			if (a->GetDistance() > b->GetDistance())
			{
				return true;
			}
			return false;
		}
	};
};