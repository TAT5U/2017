/*Scene.cpp*/

/*2017-06-11
	��� �B��
		cocos2dx�̂悤�ȃm�[�h�̎g������
				���邽�߂�Scene�v���O����*/

/****�C���N���[�h****/
#include "Scene.h"
#include "Camera.h"
#include <algorithm>
/********************/


//�R���X�g���N�^
Scene::Scene()
{
	//�ϐ��̏�����
	_pNodes.clear();
	i = 0;


	//�J�����쐬
	_pCamera = Camera::Create();
	AddChild(_pCamera);
	_pCamera->Update();
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
void Scene::AddChild(Node *pNode, bool isFade)
{
	pNode->SetParent(this);
	_pNodes.push_back(pNode);

	if (!isFade)
	{
		_pNodes[_pNodes.size() - 1]->SetNoFade();
	}
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

void Scene::Update()
{
	//�S�m�[�h��Update�֐��Ăяo��
	while (i < _pNodes.size())
	{
		_pNodes[i]->Update();

		if (_pNodes[i]->GetIsSort())
		{
			D3DXVECTOR3 v = _pCamera->GetPosition() - _pNodes[i]->GetPosition();
			_pNodes[i]->SetDistance(D3DXVec3Length(&v));
		}
		else
		{
			_pNodes[i]->SetDistance(99999999999);
		}

		i++;
	}

	//������
	i = 0;

	std::sort(_pNodes.begin(), _pNodes.end(), NodeSort());
}

void Scene::Input()
{
	//�S�m�[�h��Input�֐��Ăяo��
	while (i < _pNodes.size())
	{
		_pNodes[i]->Input();
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
			_pNodes.erase(_pNodes.begin() + i);
			break;
		}
		i++;
	}
	i = 0;
}