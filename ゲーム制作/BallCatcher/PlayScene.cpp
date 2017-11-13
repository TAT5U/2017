/*PlayScene.cpp*/

/*2017-02-11
TAT5U
プレイシーン*/

#include "PlayScene.h"
#include<time.h>

PlayScene::PlayScene()
{
	//初期化
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

	//動的初期化
	{
		obj = new Sprite *[n];
		objpos = new Point[n];
		flg = new int[n];
		objRect = new MyRect[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	//乱数
	srand(time(NULL));
}
PlayScene::~PlayScene()
{

}

void PlayScene::Init()
{


	//バックグラウンド表示
	{
		backGround = Sprite::Create("Assets//bk.png");
		backGround->SetAnchorPoint(0, 0);
		backGround->SetPosition(0, 0);
		AddChild(backGround);
	}

	//カーソル(basket)表示
	{
		cursor = Sprite::Create("Assets//basket.png");
		cursor->SetPosition(g.WINDOW_WIDTH / 2, g.WINDOW_HEIGHT - g.WINDOW_HEIGHT / 10);
		AddChild(cursor);
	}

	//最初のオブジェクト設定
	while (i<n)
	{
		//オブジェクト設定
		SetObj();
		i++;
	}

	//使用後初期化
	i = 0;


	//スコア表示
	{
		wsprintf(text, TEXT("SCORE  %d"), score);
		scoreText = Label::Create(text, "MS ゴシック", 40);
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
				startTimeText = Label::Create(timeText, "MS ゴシック", 60);
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
			//カーソルの範囲取得
			cursorRect = MyRect(cursor->GetPosition().x - 25, cursor->GetPosition().y - cursor->GetSize().y / 2, 50, 1);

			//オブジェクトの監視 
			while (i<n)
			{
				//オブジェクトの範囲取得
				objRect[i] = obj[i]->GetBoundingBox();

				//衝突判定
				if (objRect[i].IntersectsRect(cursorRect))
				{
					//ボールの場合
					if (flg[i] == 1)
					{
						//スコア増
						score = score + 5;

						//一定個数入ったらスピード変更
						if (score>30)
						{
							speedFlg = true;
						}

						//スコア表示更新
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

						//レベルアップカウント
						cnt++;

						//オブジェクトの消去
						obj[i]->RemoveFromParent();

						//オブジェクト設定
						SetObj();
					}

					//ボール以外
					else
					{
						g.pFade->FadeOut(backGround);
						g.pFade->FadeOut(cursor);
						g.pFade->FadeOut(scoreText);
						fadeFlg = true;
					}
				}

				//落下速度
				FallObj();

				//画面外に出たらやり直し
				if (obj[i]->GetPosition().y >= g.WINDOW_HEIGHT)
				{
					obj[i]->RemoveFromParent();
					SetObj();
				}

				//レベルアップ
				if (cnt >= 5)
				{
					i = 0;
					LvUpObj();
					cnt = 0;
				}
				i++;
			}

			//使用後初期化
			i = 0;
		}
	}
}
void PlayScene::Input()
{
	cursor->SetPosition(g.pInput->GetMousePos().pX, cursor->GetPosition().y);
}
//オブジェクト設定
void PlayScene::SetObj()
{
	//ランダムに変更
	flg[i] = rand() % (3 - 1 + 1) + 1;

	//ボール・紙くず・ビン
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

	//速度レベル変更可の時のフラグ有効化
	spobjFlg[i] = true;

	//ランダムな位置にする
	obj[i]->SetPosition(rand() % ((0 + 10) - g.WINDOW_WIDTH - 10 + 1), -50);
	AddChild(obj[i]);
}
//レベルアップ時
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

	//使用後初期化
	i = 0;

	//オブジェクト数増加
	n++;

	//動的の解放と初期化
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
		//最後
		if (i >= n - 1)
		{
			//オブジェクト設定
			SetObj();
		}
		//最後以外 オブジェクトを変更させないため
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

			//速度レベル変更可の時のフラグ有効化
			spobjFlg[i] = true;

			//位置を元の位置と同じに
			obj[i]->SetPosition(pos[i].pX, pos[i].pY);
			AddChild(obj[i]);
		}
		i++;
	}

	//使用後初期化
	i = 0;

	//動的(work)の解放
	{
		delete[]workflg;
		delete[]pos;
	}
}
//落下速度
void PlayScene::FallObj()
{
	objpos[i].pX = obj[i]->GetPosition().x;
	objpos[i].pY = obj[i]->GetPosition().y;

	//最初の速度
	if (speedFlg == false)
	{
		objpos[i].pY += 3;

	}

	//速度レベル変更時
	else
	{
		//速度レベルを乱数で振り分け
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

		//画面外に出るまで速度レベルを変更しない
		spobjFlg[i] = false;
	}

	//落下先の位置を格納
	obj[i]->SetPosition(objpos[i].pX, objpos[i].pY);
}