/*PlayScene.cpp*/

#include "PlayScene.h"


PlayScene::PlayScene()
{
	backGround = nullptr;
	trump[0] = nullptr;
	trump[1] = nullptr;
	player = nullptr;
	count = 0;
	turn = 0;
	clickCount = 0;
	handleOpenFlg = false;
	judge = nullptr;
	turnLabel = nullptr;
	end = nullptr;
	retry = nullptr;
	gamePlayFlg = true;
	fadeFlg = false;
	gameCount = 0;
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	//�w�i
	backGround = BackGround::Create();
	AddChild(backGround, false);

	//�v���C���[
	player = Player::Create();
	while (count < 4)
	{
		player[count]->InitializeScore(count);
		AddChild(player[count]);
		count++;
	}
	count = 0;

	//�g�����v
	trump[0] = Trump::Create();
	trump[1] = Trump::HandleCreate();
	while (count < 52)
	{
		trump[1][count]->SetPosition(trump[0][count]->GetPosition());
		trump[1][count]->SetPosition(trump[0][count]->GetPosition().x, trump[0][count]->GetPosition().y, 10);

		AddChild(trump[0][count]);
		AddChild(trump[1][count]);
		count++;
	}
	count = 0;

	//�^�[���̕\��(�]�T������΂������֐���)
	wsprintf(turnText, TEXT("�v���C���[%d�̃^�[���ł�"), turn + 1);
	turnLabel = Label::Create(turnText, "MS �S�V�b�N", 40);
	turnLabel->SetPosition(g.STANDARD_CONTENT_WIDTH, g.WINDOW_HEIGHT / 4);
	AddChild(turnLabel);
}
void PlayScene::Update()
{
	//���g���C���̃t�F�[�h���I�������܂�PlayScene�ɑJ��
	if (fadeFlg && g.pFade->GetFadeEnd())
	{
		while (count < 4)
		{
			player[count]->InitializeScore(count);
			count++;
		}
		count = 0;
		g.ReplaceScene(new PlayScene);
	}
}
void PlayScene::Input()
{
	if (g.pInput->IsMousePush(0))
	{
		RetryORExit();

		//�N���b�N����Ă��邩�ǂ����̃t���O����������false�ɂ���
		handleOpenFlg = false;

		while (count < 52)
		{
			//�O�����Z�q�͌^���ꏏ�ɂ��Ȃ��Ƃ����Ȃ��̂ŃL���X�g����
			CallJudgement() == true ? static_cast<void>(count = 99) : OnClick();
			count++;
		}
		count = 0;
	}
}

//���g���C��Exit�������ꂽ�Ƃ�
void PlayScene::RetryORExit()
{
	if (!gamePlayFlg)
	{
		MyRect retryRect = retry->GetBoundingBox();
		MyRect endRect = end->GetBoundingBox();

		if (retryRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			g.pFade->FadeOut(turnLabel);
			fadeFlg = true;
		}
		else if (endRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)))
		{
			//exit�ōs���ƃ��������[�N���N����̂�
			//Main.cpp��WndProc�ŏI���������s��
			//���̂��߂̃t���O��݂��Ă��̃t���O�ɂ����
			//�I���������s��
			g.SetEndFlg(true);
		}
	}
}

//Judge�Ăяo��
bool PlayScene::CallJudgement()
{
	// Judgement
	if (clickCount >= 2 && !handleOpenFlg)
	{
		//������
		if (judge->Judgement(clickNumber))
		{
			//�g�����v�N���X�Œ�`�����ق����I�u�W�F�N�g�w��(����?)
			Trump::RemoveTrump(trump[0], clickNumber);
			Trump::RemoveTrump(trump[1], clickNumber);
			player[turn]->SetScore(5, turn);
			player[turn]->SetPlayerScore(player[turn], turn);

			//�����邽�тɔՖʂ��Ď�
			BoardMonitor();
		}
		else
		{
			//�g�����v�̕������ɖ߂�
			trump[1][clickNumber[0]]->SetPosition(trump[1][clickNumber[0]]->GetPosition().x, trump[1][clickNumber[0]]->GetPosition().y, trump[1][clickNumber[0]]->GetPosition().z - 1);
			trump[1][clickNumber[1]]->SetPosition(trump[1][clickNumber[1]]->GetPosition().x, trump[1][clickNumber[1]]->GetPosition().y, trump[1][clickNumber[1]]->GetPosition().z - 1);

			//������x�N���b�N�ł���悤�Ƀt���O��ύX
			trump[0][clickNumber[0]]->SetTurnFlag(false, clickNumber[0]);
			trump[0][clickNumber[1]]->SetTurnFlag(false, clickNumber[1]);

			//�^�[���ύX
			ChangeTurn();

			//�^�[���\��(�]�T������΂������֐���)
			wsprintf(turnText, TEXT("�v���C���[%d�̃^�[���ł�"), turn + 1);
			turnLabel->SetString(turnText);
		}
		clickCount = 0;
		return true;
	}
	return false;
}

//�Ֆʂ̊Ď�
void PlayScene::BoardMonitor()
{
	//�Q�[���J�E���g���ăg�����v�����ׂĂȂ��Ȃ�ΏI���̕\��
	gameCount++;
	if (gameCount >= 26)
	{
		gamePlayFlg = false;

		int win = judge->GetWinner(player);

		//���ҕ\��
		wsprintf(turnText, TEXT("�v���C���[%d�̏����ł�"), win);
		turnLabel->SetString(turnText);

		//���g���C
		retry = Sprite::Create("Assets//Retry.png");
		retry->SetPosition(g.STANDARD_CONTENT_WIDTH / 2, g.STANDARD_CONTENT_HEIGHT);
		retry->SetScale(0.50f, 0.50f);
		AddChild(retry);

		//�I��
		end = Sprite::Create("Assets//Exit.png");
		end->SetPosition(g.STANDARD_CONTENT_WIDTH + retry->GetPosition().x, g.STANDARD_CONTENT_HEIGHT);
		end->SetScale(0.50f, 0.50f);
		AddChild(end);
	}
}

//�^�[���ύX
void PlayScene::ChangeTurn()
{
	turn++;
	if (turn > 3)
	{
		turn = 0;
	}
}

//�g�����v�̃N���b�N��
void PlayScene::OnClick()
{
	//�g�����v���N���b�N������
	if (!trump[0][count]->GetTurnFlag(count))
	{
		MyRect trumpRect = trump[0][count]->GetBoundingBox();

		//�g�����v�̂Ƃ�����N���b�N���Ă��邩�ǂ���
		if (trumpRect.ContainsPoint(g.pInput->GetMousePos()))
		{
			//�t���O��ύX���ăN���b�N�����Ƃ���̗v�f���L��
			//�����ăg�����v�̕���Z��1���Ɉړ�������
			trump[0][count]->SetTurnFlag(true, count);
			trump[1][count]->SetPosition(trump[1][count]->GetPosition().x, trump[1][count]->GetPosition().y, trump[1][count]->GetPosition().z + 1);
			clickNumber[clickCount] = count;
			clickCount++;
		}

		//�N���b�N���̃t���O��ύX
		//�����ŕύX���邱�Ƃɂ���Ĕ��莞�̏������ł���(�N���b�N����܂Ńg�����v�̐�����������)
		handleOpenFlg = true;
	}
}
