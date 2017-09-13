/*Scene.cpp*/

/*2017-06-11
	狩野 達哉
		cocos2dxのようなノードの使い方を
				するためのSceneプログラム*/

/****インクルード****/
#include "Scene.h"
/********************/


//コンストラクタ
Scene::Scene()
{
	//変数の初期化
	_nodes.clear();
	i = 0;
}

//デストラクタ
Scene::~Scene()
{
	while (i < _nodes.size())
	{
		delete _nodes[i];
		i++;
	}

	//初期化
	i = 0;
}

//ノード(スプライト)を追加
void Scene::AddChild(Node *pNode)
{
	pNode->SetParent(this);
	_nodes.push_back(pNode);
}

//描画処理
void Scene::Draw()
{
	//全ノードのDraw関数呼び出し
	while (i < _nodes.size())
	{
		_nodes[i]->Draw();
		i++;
	}

	//初期化
	i = 0;
}


//ノード削除
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