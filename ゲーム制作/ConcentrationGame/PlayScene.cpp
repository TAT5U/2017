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
	//背景
	backGround = BackGround::Create();
	AddChild(backGround, false);

	//プレイヤー
	player = Player::Create();
	while (count < 4)
	{
		player[count]->InitializeScore(count);
		AddChild(player[count]);
		count++;
	}
	count = 0;

	//トランプ
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

	//ターンの表示(余裕があればここを関数化)
	wsprintf(turnText, TEXT("プレイヤー%dのターンです"), turn + 1);
	turnLabel = Label::Create(turnText, "MS ゴシック", 40);
	turnLabel->SetPosition(g.STANDARD_CONTENT_WIDTH, g.WINDOW_HEIGHT / 4);
	AddChild(turnLabel);
}
void PlayScene::Update()
{
	//リトライ時のフェードが終わったらまたPlaySceneに遷移
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

		//クリックされているかどうかのフラグをいったんfalseにする
		handleOpenFlg = false;

		while (count < 52)
		{
			//三項演算子は型を一緒にしないといけないのでキャストする
			CallJudgement() == true ? static_cast<void>(count = 99) : OnClick();
			count++;
		}
		count = 0;
	}
}

//リトライかExitが押されたとき
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
			//exitで行うとメモリリークが起こるので
			//Main.cppのWndProcで終了処理を行う
			//そのためのフラグを設けてそのフラグによって
			//終了処理を行う
			g.SetEndFlg(true);
		}
	}
}

//Judge呼び出し
bool PlayScene::CallJudgement()
{
	// Judgement
	if (clickCount >= 2 && !handleOpenFlg)
	{
		//当たり
		if (judge->Judgement(clickNumber))
		{
			//トランプクラスで定義したほうがオブジェクト指向(多分?)
			Trump::RemoveTrump(trump[0], clickNumber);
			Trump::RemoveTrump(trump[1], clickNumber);
			player[turn]->SetScore(5, turn);
			player[turn]->SetPlayerScore(player[turn], turn);

			//当たるたびに盤面を監視
			BoardMonitor();
		}
		else
		{
			//トランプの柄を元に戻す
			trump[1][clickNumber[0]]->SetPosition(trump[1][clickNumber[0]]->GetPosition().x, trump[1][clickNumber[0]]->GetPosition().y, trump[1][clickNumber[0]]->GetPosition().z - 1);
			trump[1][clickNumber[1]]->SetPosition(trump[1][clickNumber[1]]->GetPosition().x, trump[1][clickNumber[1]]->GetPosition().y, trump[1][clickNumber[1]]->GetPosition().z - 1);

			//もう一度クリックできるようにフラグを変更
			trump[0][clickNumber[0]]->SetTurnFlag(false, clickNumber[0]);
			trump[0][clickNumber[1]]->SetTurnFlag(false, clickNumber[1]);

			//ターン変更
			ChangeTurn();

			//ターン表示(余裕があればここを関数化)
			wsprintf(turnText, TEXT("プレイヤー%dのターンです"), turn + 1);
			turnLabel->SetString(turnText);
		}
		clickCount = 0;
		return true;
	}
	return false;
}

//盤面の監視
void PlayScene::BoardMonitor()
{
	//ゲームカウントしてトランプがすべてなくなれば終了の表示
	gameCount++;
	if (gameCount >= 26)
	{
		gamePlayFlg = false;

		int win = judge->GetWinner(player);

		//勝者表示
		wsprintf(turnText, TEXT("プレイヤー%dの勝ちです"), win);
		turnLabel->SetString(turnText);

		//リトライ
		retry = Sprite::Create("Assets//Retry.png");
		retry->SetPosition(g.STANDARD_CONTENT_WIDTH / 2, g.STANDARD_CONTENT_HEIGHT);
		retry->SetScale(0.50f, 0.50f);
		AddChild(retry);

		//終了
		end = Sprite::Create("Assets//Exit.png");
		end->SetPosition(g.STANDARD_CONTENT_WIDTH + retry->GetPosition().x, g.STANDARD_CONTENT_HEIGHT);
		end->SetScale(0.50f, 0.50f);
		AddChild(end);
	}
}

//ターン変更
void PlayScene::ChangeTurn()
{
	turn++;
	if (turn > 3)
	{
		turn = 0;
	}
}

//トランプのクリック時
void PlayScene::OnClick()
{
	//トランプをクリックした時
	if (!trump[0][count]->GetTurnFlag(count))
	{
		MyRect trumpRect = trump[0][count]->GetBoundingBox();

		//トランプのところをクリックしているかどうか
		if (trumpRect.ContainsPoint(g.pInput->GetMousePos()))
		{
			//フラグを変更してクリックしたところの要素を記憶
			//そしてトランプの柄のZを1つ奥に移動させる
			trump[0][count]->SetTurnFlag(true, count);
			trump[1][count]->SetPosition(trump[1][count]->GetPosition().x, trump[1][count]->GetPosition().y, trump[1][count]->GetPosition().z + 1);
			clickNumber[clickCount] = count;
			clickCount++;
		}

		//クリック時のフラグを変更
		//ここで変更することによって判定時の処理ができる(クリックするまでトランプの数字を見せる)
		handleOpenFlg = true;
	}
}
