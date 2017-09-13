/*Scene.cpp*/

/*2017-06-11
	��� �B��
		cocos2dx�̂悤�ȃm�[�h�̎g������
				���邽�߂�Scene�v���O����*/

/****�C���N���[�h****/
#include "Scene.h"
/********************/


//�R���X�g���N�^
Scene::Scene()
{
	//�ϐ��̏�����
	_nodes.clear();
	i = 0;
}

//�f�X�g���N�^
Scene::~Scene()
{
	while (i < _nodes.size())
	{
		delete _nodes[i];
		i++;
	}

	//������
	i = 0;
}

//�m�[�h(�X�v���C�g)��ǉ�
void Scene::AddChild(Node *pNode)
{
	pNode->SetParent(this);
	_nodes.push_back(pNode);
}

//�`�揈��
void Scene::Draw()
{
	//�S�m�[�h��Draw�֐��Ăяo��
	while (i < _nodes.size())
	{
		_nodes[i]->Draw();
		i++;
	}

	//������
	i = 0;
}


//�m�[�h�폜
void Scene::RemoveChild(Node *pNode)
{
	while (i < _nodes.size())
	{
		if (pNode == _nodes[i])
		{
			SAFE_DELETE(_nodes[i]);
			_nodes.erase(_nodes.begin());
			break;
		}
		i++;
	}
	i = 0;
}