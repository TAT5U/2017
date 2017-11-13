/*PlayScene.cpp*/

/*2017-02-11
TAT5U
�v���C�V�[��*/

#include "PlayScene.h"
#include<time.h>

PlayScene::PlayScene()
{
	//������
	cursor = nullptr;
	backGround = nullptr;
	pos = nullptr;
	workflg = nullptr;

	n = 3;
	i = 0;
	cnt = 0;
	score = 0;
	prevDigit = 0;
	scoreText = nullptr;
	startTimeText = nullptr;
	speedFlg = false;
	timeFlg = false;
	startTime = 4;
	cursorRect = MyRect();
	fadeFlg = false;

	//���I������
	{
		obj = new Sprite *[n];
		objpos = new Point[n];
		flg = new int[n];
		objRect = new MyRect[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	//����
	srand(time(NULL));
}
PlayScene::~PlayScene()
{

}

void PlayScene::Init()
{


	//�o�b�N�O���E���h�\��
	{
		backGround = Sprite::Create("Assets//bk.png");
		backGround->SetAnchorPoint(0, 0);
		backGround->SetPosition(0, 0);
		AddChild(backGround);
	}

	//�J�[�\��(basket)�\��
	{
		cursor = Sprite::Create("Assets//basket.png");
		cursor->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT - g.WINDOW_HEIGHT / 10);
		AddChild(cursor);
	}

	//�ŏ��̃I�u�W�F�N�g�ݒ�
	while (i<n)
	{
		//�I�u�W�F�N�g�ݒ�
		SetObj();
		i++;
	}

	//�g�p�㏉����
	i = 0;


	//�X�R�A�\��
	{
		wsprintf(text, TEXT("SCORE  %d"), score);
		scoreText = Label::Create(text, "MS �S�V�b�N", 40);
		scoreText->SetPosition(g.WINDOW_WIDTH - 100, 20);
		AddChild(scoreText);
	}
	g.pFade->FadeIn(backGround);
	g.pFade->FadeIn(cursor);
}
void PlayScene::Update()
{
	if ((fadeFlg) && g.pFade->GetFadeEnd())
	{
		g.ReplaceScene(new GameOverScene);
	}

	if ((!g.GetFadeFlg()) && (!fadeFlg))
	{
		startTime = startTime - 0.10f;
		if (startTime > 1.0f)
		{
			sprintf(timeText, TEXT("%d"), (int)startTime);
			if (startTimeText == nullptr)
			{
				startTimeText = Label::Create(timeText, "MS �S�V�b�N", 60);
				startTimeText->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT / 2);
				AddChild(startTimeText);
			}
			startTimeText->SetString(timeText);
		}
		else
		{
			if (!timeFlg)
			{
				startTimeText->RemoveFromParent();
				timeFlg = true;
			}
			//�J�[�\���͈͎̔擾
			cursorRect = MyRect(cursor->GetPosition().x - 25, cursor->GetPosition().y - cursor->GetSize().y / 2, 50, 1);

			//�I�u�W�F�N�g�̊Ď� 
			while (i<n)
			{
				//�I�u�W�F�N�g�͈͎̔擾
				objRect[i] = obj[i]->GetBoundingBox();

				//�Փ˔���
				if (objRect[i].IntersectsRect(cursorRect))
				{
					//�{�[���̏ꍇ
					if (flg[i] == 1)
					{
						//�X�R�A��
						score = score + 5;

						//������������X�s�[�h�ύX
						if (score>30)
						{
							speedFlg = true;
						}

						//�X�R�A�\���X�V
						wsprintf(text, TEXT("SCORE  %d"), score);
						scoreText->SetString(text);
						int digit = 0, scoreNum = score, scorePos = 0;
						while (scoreNum != 0)
						{
							scoreNum /= 10;
							digit++;
						}
						if (prevDigit < digit)
						{
							while (scorePos < prevDigit - 2)
							{
								scoreText->SetPosition(scoreText->GetPosition().x + 10, scoreText->GetPosition().y);
								scorePos++;
							}
							scorePos = 0;
							prevDigit = digit;
							while (scorePos < digit - 2)
							{
								scoreText->SetPosition(scoreText->GetPosition().x - 10, scoreText->GetPosition().y);
								scorePos++;
							}
						}

						//���x���A�b�v�J�E���g
						cnt++;

						//�I�u�W�F�N�g�̏���
						obj[i]->RemoveFromParent();

						//�I�u�W�F�N�g�ݒ�
						SetObj();
					}

					//�{�[���ȊO
					else
					{
						g.pFade->FadeOut(backGround);
						g.pFade->FadeOut(cursor);
						g.pFade->FadeOut(scoreText);
						fadeFlg = true;
					}
				}

				//�������x
				FallObj();

				//��ʊO�ɏo�����蒼��
				if (obj[i]->GetPosition().y >= g.WINDOW_HEIGHT)
				{
					obj[i]->RemoveFromParent();
					SetObj();
				}

				//���x���A�b�v
				if (cnt >= 5)
				{
					i = 0;
					LvUpObj();
					cnt = 0;
				}
				i++;
			}

			//�g�p�㏉����
			i = 0;
		}
	}
}
void PlayScene::Input()
{
	cursor->SetPosition(g.pInput->GetMousePos().pX, cursor->GetPosition().y);
}
//�I�u�W�F�N�g�ݒ�
void PlayScene::SetObj()
{
	//�����_���ɕύX
	flg[i] = rand() % (3 - 1 + 1) + 1;

	//�{�[���E�������E�r��
	if (flg[i] == 1)
	{
		obj[i] = Sprite::Create("Assets\\ball.png");
	}
	else if (flg[i] == 2)
	{
		obj[i] = Sprite::Create("Assets\\paper.png");
	}
	else if (flg[i] == 3)
	{
		obj[i] = Sprite::Create("Assets\\bin.png");
	}

	//���x���x���ύX�̎��̃t���O�L����
	spobjFlg[i] = true;

	//�����_���Ȉʒu�ɂ���
	obj[i]->SetPosition(rand() % ((0 + 10) - g.WINDOW_WIDTH - 10 + 1), -50);
	AddChild(obj[i]);
}
//���x���A�b�v��
void PlayScene::LvUpObj()
{
	workflg = new int[n];
	pos = new Point[n];
	while (i < n)
	{
		workflg[i] = flg[i];
		pos[i].pX = obj[i]->GetPosition().x;
		pos[i].pY = obj[i]->GetPosition().y;
		obj[i]->RemoveFromParent();
		i++;
	}

	//�g�p�㏉����
	i = 0;

	//�I�u�W�F�N�g������
	n++;

	//���I�̉���Ə�����
	{
		delete[]obj;
		delete[]flg;
		delete[]objRect;
		delete[]objpos;
		delete[]spFlg;
		delete[] spobjFlg;

		obj = new Sprite *[n];
		flg = new int[n];
		objRect = new MyRect[n];
		objpos = new Point[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	while (i<n)
	{
		//�Ō�
		if (i >= n - 1)
		{
			//�I�u�W�F�N�g�ݒ�
			SetObj();
		}
		//�Ō�ȊO �I�u�W�F�N�g��ύX�����Ȃ�����
		else
		{
			flg[i] = workflg[i];
			if (flg[i] == 1)
			{
				obj[i] = Sprite::Create("Assets\\ball.png");

			}
			else if (flg[i] == 2)
			{
				obj[i] = Sprite::Create("Assets\\paper.png");

			}
			else if (flg[i] == 3)
			{
				obj[i] = Sprite::Create("Assets\\bin.png");

			}

			//���x���x���ύX�̎��̃t���O�L����
			spobjFlg[i] = true;

			//�ʒu�����̈ʒu�Ɠ�����
			obj[i]->SetPosition(pos[i].pX, pos[i].pY);
			AddChild(obj[i]);
		}
		i++;
	}

	//�g�p�㏉����
	i = 0;

	//���I(work)�̉��
	{
		delete[]workflg;
		delete[]pos;
	}
}
//�������x
void PlayScene::FallObj()
{
	objpos[i].pX = obj[i]->GetPosition().x;
	objpos[i].pY = obj[i]->GetPosition().y;

	//�ŏ��̑��x
	if (speedFlg == false)
	{
		objpos[i].pY += 3;

	}

	//���x���x���ύX��
	else
	{
		//���x���x���𗐐��ŐU�蕪��
		if (spobjFlg[i] == true)
		{
			spFlg[i] = rand() % (3 - 1 + 1) + 1;
		}
		if (spFlg[i] == 1)
		{
			objpos[i].pY += 2;
		}
		else if (spFlg[i] == 2)
		{
			objpos[i].pY += 5;
		}
		else if (spFlg[i] == 3)
		{
			objpos[i].pY += 1;
		}

		//��ʊO�ɏo��܂ő��x���x����ύX���Ȃ�
		spobjFlg[i] = false;
	}

	//������̈ʒu���i�[
	obj[i]->SetPosition(objpos[i].pX, objpos[i].pY);
}