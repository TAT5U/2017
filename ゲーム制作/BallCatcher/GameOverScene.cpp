/*GameOverScene.cpp*/

#include "GameOverScene.h"
GameOverScene::GameOverScene()
{
	backGround = nullptr;
	gameOver = nullptr;
	retry = nullptr;
	end = nullptr;
	fadeFlg = false;
}
GameOverScene::~GameOverScene()
{

}

void GameOverScene::Init()
{
	//バックグラウンド表示
	{
		backGround = Sprite::Create("Assets//bk.png");
		backGround->SetAnchorPoint(0, 0);
		backGround->SetPosition(0, 0);
		AddChild(backGround);
	}

	//ゲームオーバー
	{
		gameOver = Sprite::Create("Assets//GameOver.png");
		gameOver->SetScale(0.50f, 0.50f);
		gameOver->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT / 2);
		AddChild(gameOver);
	}

	//リトライ
	{
		retry = Sprite::Create("Assets//Retry.png");
		retry->SetScale(0.40f, 0.40f);
		retry->SetPosition(g.WINDOW_WIDTH / 3.0f, g.WINDOW_HEIGHT / 1.70f);
		AddChild(retry);
	}

	//終了
	{
		end = Sprite::Create("Assets//Exit.png");
		end->SetScale(0.40f, 0.40f);
		end->SetPosition(g.WINDOW_WIDTH / 1.50f, g.WINDOW_HEIGHT / 1.70f);
		AddChild(end);
	}

	g.pFade->FadeIn(backGround);
	g.pFade->FadeIn(gameOver);
	g.pFade->FadeIn(retry);
	g.pFade->FadeIn(end);

}
void GameOverScene::Update()
{
}
void GameOverScene::Input()
{
	//クリックしたかどうか
	if (g.pInput->IsMousePush(0))
	{
		MyRect retryRect = retry->GetBoundingBox();
		MyRect endRect = end->GetBoundingBox();

		//クリックしたものによって切り替え
		if (retryRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			g.ReplaceScene(new PlayScene);
		}
		else if (endRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			exit(1);
		}
	}
}
