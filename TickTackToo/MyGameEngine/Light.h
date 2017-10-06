/*Light.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include"Node.h"
/********************/


//ライトを使用するためのクラス
//Nodeクラスを継承
class Light : public Node
{
public:

	//デストラクタ
	~Light();

	//静的関数	ライトの作成
	//引数->なし
	//戻値->ライト
	static Light *Create();
};

