/*Scene.h*/

//インクルードガード
#pragma once

/********インクルード********/
#include "Global.h"
#include "Sprite.h"
#include "Label.h"
#include "Quad.h"
#include "Light.h"
#include "Fbx.h"

//vector型を使用可能にする
#include <vector>
/****************************/


//stdを宣言しておいて省略できるようにする
using namespace std;

class Camera;

//各ノードを表示するためのシーンクラス
class Scene
{
	//ノードの個数をカウントする変数
	int i;

	//ノード(スプライト)を追加するための動的配列
	vector<Node *> _pNodes;

protected:
	Camera *_pCamera;

public:

	//コンストラクタ
	Scene();

	//デストラクタ
	//継承されるデストラクタ
	virtual ~Scene();

	//ノード(スプライト)を追加
	//引数->描画するノード
	//戻値->なし
	void AddChild(Node *pNode, bool isFade = true);

	//描画処理
	//引数->なし
	//戻値->なし
	void Draw();

	/********************純粋仮想関数********************/
	//純粋仮想関数は最初に0を格納しておく
	//格納しないで実行してしまうとエラーを吐いてしまう
	//各シーンによって処理が違うため一緒にできない
	//引数->なし
	//戻値->なし
	virtual void Init() = 0;
	virtual void Update();
	virtual void Input();
	/****************************************************/


	//ノード削除
	void RemoveChild(Node *pNode);

	//ノードのソート
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