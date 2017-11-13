/*TitleScene.cpp*/

#include "TitleScene.h"
TitleScene::TitleScene()
{
	backGround = nullptr;
	title = nullptr;
	fadeFlg = false;
}
TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	//バックグラウンド表示
	{
		backGround = Sprite::Create("Assets//bk.png");
		backGround->SetAnchorPoint(0, 0);
		backGround->SetPosition(0, 0);
		AddChild(backGround);
	}

	//タイトル
	{
		title = Sprite::Create("Assets//title.png");
		title->SetScale(0.50f, 0.50f);
		title->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT / 2);
		AddChild(title);
	}
}
void TitleScene::Update()
{
	//シーン切り替え
	if ((fadeFlg) && g.pFade->GetFadeEnd())
	{
		g.ReplaceScene(new PlayScene);
	}

}
void TitleScene::Input()
{
	//クリックしたか判定
	if (g.pInput->IsMousePush(0))
	{
		g.pFade->FadeOut(backGround);
		g.pFade->FadeOut(title);
		fadeFlg = true;
	}

}
