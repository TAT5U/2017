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
	_pNodes.clear();
	i = 0;
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
void Scene::AddChild(Node *pNode)
{
	pNode->SetParent(this);
	_pNodes.push_back(pNode);
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


//ノード削除
void Scene::RemoveChild(Node *pNode)
{
	while (i < _pNodes.size())
	{
		if (pNode == _pNodes[i])
		{
			SAFE_DELETE(_pNodes[i]);

			//2017-10-04
			//修正
			//iのカウントがなかった
			_pNodes.erase(_pNodes.begin() + i);
			break;
		}
		i++;
	}
	i = 0;
}