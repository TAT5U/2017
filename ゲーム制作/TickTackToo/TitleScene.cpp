/*PlayScene.cpp*/

/*2017-06-16
��� �B��
�v���C�V�[���̃v���O����*/

/****�C���N���[�h****/
#include "TitleScene.h"
/********************/


//�R���X�g���N�^
TitleScene::TitleScene()
{
	//�ϐ��̏�����
	backGround = nullptr;
	title = nullptr;
	start = nullptr;
	alpha = 255;
	fadeFlg = false;
	isFadeFlg = false;
}
//�f�X�g���N�^
TitleScene::~TitleScene()
{

}

//����������
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

//�X�V����
void TitleScene::Update()
{
	
	if (fadeFlg && g.pFade->GetFadeEnd())
	{
		g.ReplaceScene(new PlayScene);
		fadeFlg = false;
	}
}

//���͏���
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
