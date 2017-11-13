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
	//�o�b�N�O���E���h�\��
	{
		backGround = Sprite::Create("Assets//bk.png");
		backGround->SetAnchorPoint(0, 0);
		backGround->SetPosition(0, 0);
		AddChild(backGround);
	}

	//�Q�[���I�[�o�[
	{
		gameOver = Sprite::Create("Assets//GameOver.png");
		gameOver->SetScale(0.50f, 0.50f);
		gameOver->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT / 2);
		AddChild(gameOver);
	}

	//���g���C
	{
		retry = Sprite::Create("Assets//Retry.png");
		retry->SetScale(0.40f, 0.40f);
		retry->SetPosition(g.WINDOW_WIDTH / 3.0f, g.WINDOW_HEIGHT / 1.70f);
		AddChild(retry);
	}

	//�I��
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
	//�N���b�N�������ǂ���
	if (g.pInput->IsMousePush(0))
	{
		MyRect retryRect = retry->GetBoundingBox();
		MyRect endRect = end->GetBoundingBox();

		//�N���b�N�������̂ɂ���Đ؂�ւ�
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
