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
	//背景
	backGround = BackGround::Create();
	AddChild(backGround, false);

	//タイトル
	title = Sprite::Create("Assets//Title.png");
	title->SetPosition(g.STANDARD_CONTENT_WIDTH, g.STANDARD_CONTENT_HEIGHT);
	AddChild(title);

}
void TitleScene::Update()
{
	//フェードが終わったらシーン遷移
	if (fadeFlg && g.pFade->GetFadeEnd())
	{
		g.ReplaceScene(new PlayScene);
	}
}
void TitleScene::Input()
{
	//タイトルがクリックされたらフェード開始
	if ((g.pInput->IsMousePush(0)) && (!fadeFlg))
	{
		MyRect startRect = title->GetBoundingBox();
		if (startRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			g.pFade->FadeOut(title);
			fadeFlg = true;
		}
	}
}
