/*Scene.h*/

//インクルードガード
#pragma once

/********インクルード********/
#include "Global.h"
#include "Sprite.h"
#include "Label.h"
#include "Quad.h"
#include "Light.h"

//vector型を使用可能にする
#include <vector>
/****************************/


//stdを宣言しておいて省略できるようにする
using namespace std;

//各ノードを表示するためのシーンクラス
class Scene
{
	//ノードの個数をカウントする変数
	int i;

	//ノード(スプライト)を追加するための動的配列
	vector<Node *> _pNodes;

public:

	//コンストラクタ
	Scene();

	//デストラクタ
	//継承されるデストラクタ
	virtual ~Scene();

	//ノード(スプライト)を追加
	//引数->描画するノード
	//戻値->なし
	void AddChild(Node *pNode);

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
	virtual void Update() = 0;
	virtual void Input() = 0;
	/****************************************************/


	//ノード削除
	void RemoveChild(Node *pNode);
};