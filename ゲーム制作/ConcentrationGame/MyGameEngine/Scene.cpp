/*Scene.cpp*/

/*2017-06-11
	狩野 達哉
		cocos2dxのようなノードの使い方を
				するためのSceneプログラム*/

/****インクルード****/
#include "Scene.h"
#include "Camera.h"
#include <algorithm>
/********************/


//コンストラクタ
Scene::Scene()
{
	//変数の初期化
	_pNodes.clear();
	i = 0;


	//カメラ作成
	_pCamera = Camera::Create();
	AddChild(_pCamera);
	_pCamera->Update();
}

//デストラクタ
Scene::~Scene()
{
	//シーン自動解放
	while (i < _pNodes.size())
	{
		SAFE_DELETE(_pNodes[i]);
		i++;
	}

	//初期化
	i = 0;
}

//ノード(スプライト)を追加
void Scene::AddChild(Node *pNode, bool isFade)
{
	pNode->SetParent(this);
	_pNodes.push_back(pNode);

	if (!isFade)
	{
		_pNodes[_pNodes.size() - 1]->SetNoFade();
	}
}

//描画処理
void Scene::Draw()
{
	//全ノードのDraw関数呼び出し
	while (i < _pNodes.size())
	{
		_pNodes[i]->Draw();
		i++;
	}

	//初期化
	i = 0;
}

void Scene::Update()
{
	//全ノードのUpdate関数呼び出し
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

	//初期化
	i = 0;

	std::sort(_pNodes.begin(), _pNodes.end(), NodeSort());
}

void Scene::Input()
{
	//全ノードのInput関数呼び出し
	while (i < _pNodes.size())
	{
		_pNodes[i]->Input();
		i++;
	}

	//初期化
	i = 0;
}

//ノード削除
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