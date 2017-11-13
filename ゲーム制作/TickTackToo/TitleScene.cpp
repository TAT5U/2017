/*PlayScene.cpp*/

/*2017-06-16
狩野 達哉
プレイシーンのプログラム*/

/****インクルード****/
#include "TitleScene.h"
/********************/


//コンストラクタ
TitleScene::TitleScene()
{
	//変数の初期化
	backGround = nullptr;
	title = nullptr;
	start = nullptr;
	alpha = 255;
	fadeFlg = false;
	isFadeFlg = false;
}
//デストラクタ
TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Init()
{
	backGround = Sprite::Create("Assets/TitleBackGround.png");
	backGround->SetAnchorPoint(0, 0);
	backGround->SetPosition(0, 0);
	AddChild(backGround);

	title = Sprite::Create("Assets/Title.png");
	title->SetPosition(g.WINDOW_WIDTH * 0.50f, g.WINDOW_HEIGHT * 0.50f);
	AddChild(title);

	start = Sprite::Create("Assets/Start.png");
	start->SetPosition(g.WINDOW_WIDTH * 0.50f, title->GetPosition().y + title->GetSize().y * 0.250f);
	AddChild(start);
}

//更新処理
void TitleScene::Update()
{
	
	if (fadeFlg && g.pFade->GetFadeEnd())
	{
		g.ReplaceScene(new PlayScene);
		fadeFlg = false;
	}
}

//入力処理
void TitleScene::Input()
{
	if (g.pInput->IsMousePush(0))
	{
		MyRect startRect = start->GetBoundingBox();
		if (startRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			g.pFade->FadeOut(backGround);
			g.pFade->FadeOut(title);
			g.pFade->FadeOut(start);
			fadeFlg = true;
		}
	}
}
