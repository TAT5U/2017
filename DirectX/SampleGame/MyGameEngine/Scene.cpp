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
	_pNodes.clear();
	i = 0;
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�V�[���������
	while (i < _pNodes.size())
	{
		SAFE_DELETE(_pNodes[i]);
		i++;
	}

	//������
	i = 0;
}

//�m�[�h(�X�v���C�g)��ǉ�
void Scene::AddChild(Node *pNode)
{
	pNode->SetParent(this);
	_pNodes.push_back(pNode);
}

//�`�揈��
void Scene::Draw()
{
	//�S�m�[�h��Draw�֐��Ăяo��
	while (i < _pNodes.size())
	{
		_pNodes[i]->Draw();
		i++;
	}

	//������
	i = 0;
}


//�m�[�h�폜
void Scene::RemoveChild(Node *pNode)
{
	while (i < _pNodes.size())
	{
		if (pNode == _pNodes[i])
		{
			SAFE_DELETE(_pNodes[i]);

			//2017-10-04
			//�C��
			//i�̃J�E���g���Ȃ�����
			_pNodes.erase(_pNodes.begin() + i);
			break;
		}
		i++;
	}
	i = 0;
}