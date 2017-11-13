/*PlayScene.cpp*/

/*2017-06-16
	狩野 達哉
		プレイシーンのプログラム*/

/****インクルード****/
#include "PlayScene.h"
#include<time.h>
/********************/


//コンストラクタ
PlayScene::PlayScene()
//	: frame{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr }
{
	//変数の初期化

	circle = nullptr;
	cross = nullptr;

	turnFlg = false;
	x = 0;
	y = 0;
	playCount = 0;
	gameMes = nullptr;
	frameBackGround = nullptr;
	backGround = nullptr;
	frameMes = nullptr;
	retry = nullptr;
	end = nullptr;
	isGameEnd = false;

	// Gaming End flag
	gamePlayFlg = true;


	mesFlg = false;
	waitTime = 0.0f;

	//空回し
	srand(time(NULL));
	rand();rand();rand();rand();rand();
}

//デストラクタ
PlayScene::~PlayScene()
{

}

//初期化処理
void PlayScene::Init()
{
	backGround = Sprite::Create("Assets/TitleBackGround.png");
	backGround->SetAnchorPoint(0, 0);
	backGround->SetPosition(0, 0);
	AddChild(backGround);

	frameBackGround = Sprite::Create("Assets/BackGround.png");
	frameBackGround->SetPosition(g.WINDOW_WIDTH * 0.50f, g.WINDOW_HEIGHT * 0.50f, 0.0f);
	AddChild(frameBackGround);

	frameMes = Sprite::Create("Assets/MessageFrame.png");
	frameMes->SetAnchorPoint(0, 0);
	frameMes->SetPosition(150, 0);
	AddChild(frameMes);

	g.pFade->FadeIn(backGround);
	g.pFade->FadeIn(frameBackGround);
	g.pFade->FadeIn(frameMes);

	while (y < 3)
	{
		while (x < 3)
		{
			frame[x][y] = Sprite::Create("Assets/Frame.png");
			frame[x][y]->SetAnchorPoint(0, 0);

			if ((x <= 0) && (y <= 0))
			{
				frame[x][y]->SetPosition(210, 400);
			}
			else if ((x <= 0) && (y >= 1))
			{
				frame[x][y]->SetPosition(210, frame[x][y - 1]->GetPosition().y - frame[x][y - 1]->GetSize().y);
			}
			else
			{
				frame[x][y]->SetPosition(frame[x - 1][y]->GetPosition().x + frame[x - 1][y]->GetSize().x, frame[x - 1][y]->GetPosition().y);
			}

			frameSt[x][y] = FrameState::DEFAULT;
			AddChild(frame[x][y]);
			g.pFade->FadeIn(frame[x][y]);
			x++;
		}
		x = 0;
		y++;

	}
	x = 0;
	y = 0;
}

//更新処理
void PlayScene::Update()
{
	if ((GetJudge() == Judgement::WIN) && (gamePlayFlg))
	{
		if (mesFlg)
		{
			gameMes->RemoveFromParent();
			mesFlg = false;
		}
		gameMes = Sprite::Create("Assets/WinMessage.png");
		gameMes->SetAnchorPoint(0, 0);
		gameMes->SetPosition(150, 0);
		AddChild(gameMes);
		gamePlayFlg = false;
	}
	else if ((GetJudge() == Judgement::LOSE) && (gamePlayFlg))
	{
		if (mesFlg)
		{
			gameMes->RemoveFromParent();
			mesFlg = false;
		}
		gameMes = Sprite::Create("Assets/LoseMessage.png");
		gameMes->SetAnchorPoint(0, 0);
		gameMes->SetPosition(150, 0);
		AddChild(gameMes);
		gamePlayFlg = false;
	}
	else if ((GetJudge() == Judgement::Draw) && (playCount >= 9) && (gamePlayFlg))
	{
		if (mesFlg)
		{
			gameMes->RemoveFromParent();
			mesFlg = false;
		}
		gameMes = Sprite::Create("Assets/DrawMessage.png");
		gameMes->SetAnchorPoint(0, 0);
		gameMes->SetPosition(150, 0);
		AddChild(gameMes);
		gamePlayFlg = false;
	}

	if ((!gamePlayFlg) && (!isGameEnd))
	{
		retry = Sprite::Create("Assets/Retry.png");
		retry->SetPosition(g.WINDOW_WIDTH * 0.250f, g.WINDOW_HEIGHT * 0.50f);
		AddChild(retry);

		end = Sprite::Create("Assets/End.png");
		end->SetPosition(retry->GetPosition().x + retry->GetSize().x + 150, g.WINDOW_HEIGHT * 0.50f);
		AddChild(end);
		isGameEnd = true;
	}
	if ((gamePlayFlg) && (!turnFlg) && (!g.GetFadeFlg()))
	{
		if (waitTime >= 5.0f)
		{
			SimpleAI();
			waitTime = 0.0f;
		}
		waitTime = waitTime + 0.10f;
	}
}

//入力処理
void PlayScene::Input()
{
	if (turnFlg)
	{
		if (g.pInput->IsMousePush(0) && (gamePlayFlg))
		{
			while (y < 3)
			{
				while (x < 3)
				{
					MyRect frameRect = frame[x][y]->GetBoundingBox();
					if (frameRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)) && frameSt[x][y] == DEFAULT)
					{

						circle = Sprite::Create("Assets/Circle.png");
						circle->SetAnchorPoint(0, 0);
						circle->SetPosition(frame[x][y]->GetPosition().x, frame[x][y]->GetPosition().y, frame[x][y]->GetPosition().z);
						AddChild(circle);
						frameSt[x][y] = FrameState::PLAYER;
						turnFlg = false;
						playCount++;

						if (mesFlg)
						{
							gameMes->RemoveFromParent();
							mesFlg = false;
						}
					}
					else if (frameRect.ContainsPoint(D3DXVECTOR3(g.pInput->GetMousePos().pX, g.pInput->GetMousePos().pY, 0.0f)) && frameSt[x][y] != DEFAULT && !mesFlg)
					{
						gameMes = Sprite::Create("Assets/NGClickMessage.png");
						gameMes->SetAnchorPoint(0, 0);
						gameMes->SetPosition(150, 0);
						AddChild(gameMes);
						mesFlg = true;
					}
					x++;
				}
				x = 0;
				y++;

			}
			x = 0;
			y = 0;
		}
	}

	if (g.pInput->IsMousePush(0) && (!gamePlayFlg))
	{
		MyRect retryRect = retry->GetBoundingBox();
		MyRect endRect = end->GetBoundingBox();

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

Judgement PlayScene::GetJudge()
{
	// 横
	if ((frameSt[0][0] + frameSt[1][0] + frameSt[2][0] == 3) || (frameSt[0][1] + frameSt[1][1] + frameSt[2][1] == 3) || (frameSt[0][2] + frameSt[1][2] + frameSt[2][2] == 3))
	{
		return Judgement::WIN;
	}
	else if ((frameSt[0][0] + frameSt[1][0] + frameSt[2][0] == -3) || (frameSt[0][1] + frameSt[1][1] + frameSt[2][1] == -3) || (frameSt[0][2] + frameSt[1][2] + frameSt[2][2] == -3))
	{
		return Judgement::LOSE;
	}

	// 縦
	else if ((frameSt[0][0] + frameSt[0][1] + frameSt[0][2] == 3) || (frameSt[1][0] + frameSt[1][1] + frameSt[1][2] == 3) || (frameSt[2][0] + frameSt[2][1] + frameSt[2][2] == 3))
	{
		return Judgement::WIN;
	}
	else if ((frameSt[0][0] + frameSt[0][1] + frameSt[0][2] == -3) || (frameSt[1][0] + frameSt[1][1] + frameSt[1][2] == -3) || (frameSt[2][0] + frameSt[2][1] + frameSt[2][2] == -3))
	{
		return Judgement::LOSE;
	}

	// 斜め
	// *   *
	//   *
	// *   *
	else if ((frameSt[0][0] + frameSt[1][1] + frameSt[2][2] == 3) || (frameSt[2][0] + frameSt[1][1] + frameSt[0][2] == 3))
	{
		return Judgement::WIN;
	}
	else if ((frameSt[0][0] + frameSt[1][1] + frameSt[2][2] == -3) || (frameSt[2][0] + frameSt[1][1] + frameSt[0][2] == -3))
	{
		return Judgement::LOSE;
	}

	return Judgement::Draw;
}

void PlayScene::SimpleAI()
{
	int p;
	int q;
	int cnt = 0, cnt2 = 0;
	int tag = 0, tag2 = 0;
	int AIinputX = 0, AIinputY = 0;
	bool flg = false;

	if (playCount <= 0)
	{
		p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
		q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
		AIinputX = p;
		AIinputY = q;

		while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2 || q > 2)
		{
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			AIinputY = q;
		}
	}
	else
	{
		// 横+
		while (cnt2 < 3)
		{
			if (frameSt[cnt][cnt2] + frameSt[cnt + 1][cnt2] + frameSt[cnt + 2][cnt2] == 2)
			{
				tag = cnt2;
				flg = true;
				break;
			}
			cnt2++;
		}

		// CPU
		p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
		AIinputX = p;
		q = tag;
		AIinputY = q;

		// CPU
		while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2)
		{
			if (frameSt[0][tag] != 0 && frameSt[1][tag] != 0 && frameSt[2][tag] != 0)
			{
				flg = false;
				break;
			}
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			q = tag;
			AIinputY = q;
		}
		cnt2 = 0;
		if (flg == false)
		{
			while (cnt < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == 2)
				{
					tag = cnt;
					flg = true;
					break;
				}
				cnt++;
			}
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || q > 2)
			{
				if (frameSt[tag][0] != 0 && frameSt[tag][1] != 0 && frameSt[tag][2] != 0)
				{
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;

		if (flg == false)
		{
			//	斜め+
			if (frameSt[cnt][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt + 2][cnt2 + 2] == 2)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[0][0] != 0 && frameSt[1][1] != 0 && frameSt[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{
			//	斜め2+
			if (frameSt[cnt + 2][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == 2)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frame[2][0] != 0 && frame[1][1] != 0 && frame[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;

		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt + 1][cnt2] + frameSt[cnt + 2][cnt2] == -2)
				{
					tag = cnt2;
					flg = true;
					break;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			q = tag;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frameSt[0][tag] != 0 && frameSt[1][tag] != 0 && frameSt[2][tag] != 0)
				{
					flg = false;
					break;
				}
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				AIinputX = p;
				q = tag;
				AIinputY = q;
			}
		}
		cnt2 = 0;
		if (flg == false)
		{
			while (cnt < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == -2)
				{
					tag = cnt;
					flg = true;
					break;
				}
				cnt++;
			}
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || q > 2)
			{
				if (frameSt[tag][0] != 0 && frameSt[tag][1] != 0 && frameSt[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frameSt[cnt][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt + 2][cnt2 + 2] == -2)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[0][0] != 0 && frameSt[1][1] != 0 && frameSt[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{
			//	斜め2
			if (frameSt[cnt + 2][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == -2)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[2][0] != 0 && frameSt[1][1] != 0 && frameSt[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;

		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt + 1][cnt2] + frameSt[cnt + 2][cnt2] == 1)
				{
					tag = cnt2;
					flg = true;
					break;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			q = tag;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frameSt[0][tag] != 0 && frameSt[1][tag] != 0 && frameSt[2][tag] != 0)
				{
					flg = false;
					break;
				}
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				AIinputX = p;
				q = tag;
				AIinputY = q;
			}
		}
		cnt2 = 0;
		if (flg == false)
		{
			while (cnt < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == 1)
				{
					tag = cnt;
					flg = true;
					break;
				}
				cnt++;
			}

			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || q > 2)
			{
				if (frameSt[tag][0] != 0 && frameSt[tag][1] != 0 && frameSt[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frameSt[cnt][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt + 2][cnt2 + 2] == 1)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[0][0] != 0 && frameSt[1][1] != 0 && frameSt[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{
			//	斜め2
			if (frameSt[cnt + 2][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == 1)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[2][0] != 0 && frameSt[1][1] != 0 && frameSt[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;

		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt + 1][cnt2] + frameSt[cnt + 2][cnt2] == -1)
				{
					tag = cnt2;
					flg = true;
					break;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			q = tag;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frameSt[0][tag] != 0 && frameSt[1][tag] != 0 && frameSt[2][tag] != 0)
				{
					flg = false;
					break;
				}
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				AIinputX = p;
				q = tag;
				AIinputY = q;
			}
		}
		cnt2 = 0;
		if (flg == false)
		{
			while (cnt < 3)
			{
				if (frameSt[cnt][cnt2] + frameSt[cnt][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == -1)
				{
					tag = cnt;
					flg = true;
					break;
				}
				cnt++;
			}
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || q > 2)
			{
				if (frameSt[tag][0] != 0 && frameSt[tag][1] != 0 && frameSt[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frameSt[cnt][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt + 2][cnt2 + 2] == -1)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[0][0] != 0 && frameSt[1][1] != 0 && frameSt[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{
			//	斜め2
			if (frameSt[cnt + 2][cnt] + frameSt[cnt + 1][cnt2 + 1] + frameSt[cnt][cnt2 + 2] == -1)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0)
			{
				if (frameSt[2][0] != 0 && frameSt[1][1] != 0 && frameSt[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;
				p = tag;
				q = tag2;
				AIinputX = p;
				AIinputY = q;
			}
		}
		cnt = 0;
		cnt2 = 0;

		if (flg == false)
		{
			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			AIinputX = p;
			AIinputY = q;

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frameSt[AIinputX][AIinputY] != 0 || p > 2 || q > 2)
			{
				// CPU
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				AIinputX = p;
				AIinputY = q;
			}
		}
	}

	cross = Sprite::Create("Assets/Cross.png");
	cross->SetAnchorPoint(0, 0);
	cross->SetPosition(frame[AIinputX][AIinputY]->GetPosition().x, frame[AIinputX][AIinputY]->GetPosition().y, frame[AIinputX][AIinputY]->GetPosition().z);

	AddChild(cross);
	frameSt[AIinputX][AIinputY] = FrameState::CPU;
	turnFlg = true;
	playCount++;
}