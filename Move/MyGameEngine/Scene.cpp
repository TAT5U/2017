#include "Scene.h"
#include "Camera.h"
#include <algorithm>

Scene::Scene()
{
	_camera = Camera::Create();
	this->AddChild(_camera);
	_camera->Update();
	g.pCamera = _camera;
}


Scene::~Scene()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		SAFE_DELETE(_nodes[i]);
	}
}


void Scene::AddChild(Node* pNode)
{
	pNode->SetParent(this);
	_nodes.push_back(pNode);
}

void Scene::Input()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Input();
	}
}

void Scene::Update()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Update();

		if (_nodes[i]->GetIsSort())
		{
			D3DXVECTOR3 v = _camera->GetPosition() - _nodes[i]->GetPosition();
			_nodes[i]->SetDistance(D3DXVec3Length(&v));
		}
		else
		{
			_nodes[i]->SetDistance(999999999);
		}
	}

	std::sort(_nodes.begin(), _nodes.end(), NodeSort());
}



void Scene::Draw()
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		_nodes[i]->Draw();
	}
}


void Scene::RemoveChild(Node* pNode)
{
	for (int i = 0; i < _nodes.size(); i++)
	{
		if (pNode == _nodes[i])
		{
			SAFE_DELETE(_nodes[i]);
			_nodes.erase(_nodes.begin() + i);
			break;
		}
	}
}