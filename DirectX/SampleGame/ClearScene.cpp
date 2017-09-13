/*ClearScene.cpp*/

/*2017-07-04
	狩野 達哉
		クリアシーンのプログラム*/

/****インクルード****/
#include "ClearScene.h"
/********************/


//コンストラクタ
ClearScene::ClearScene()
{

}

//デストラクタ
ClearScene::~ClearScene()
{

}

//初期化処理
void ClearScene::Init()
{
	//画像の表示
	{
		Sprite *sprite = Sprite::Create("Assets//jag.png");
		sprite->SetAnchorPoint(0, 0);
		sprite->SetPosition(100, 100);
		this->AddChild(sprite);
	}

}

//更新処理
void ClearScene::Update()
{

}

//入力処理
void ClearScene::Input()
{

}