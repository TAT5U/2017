/*Trump.cpp*/

#include "Trump.h"

//staticなので外部で宣言
bool Trump::turnFlg[52];

Trump::Trump()
{
	//turnFlg = false;
}


Trump::~Trump()
{
	
}

//トランプ配置
Trump **Trump::Create()
{
	//アクセスが多い変数にregisterをつけて高速化
	register int count = 0;

	int trumpX = 0, trumpY = 0;

	//staticにより保持
	static Trump *trump[52];

	while (count < TRUMP_MAX)
	{
		trump[count] = static_cast<Trump*>(Sprite::Create("Assets//Card.png", MyRect(trumpX, trumpY, TRUMP_WIDTH, TRUMP_HEIGHT)));
		trump[count]->SetAnchorPoint(0, 0);
		trump[count]->SetScale(0.50f, 0.50f);
		trump[count]->SetPosition(g.WINDOW_WIDTH / 25 + trumpX * trump[count]->GetScale().x * 1.150f, g.STANDARD_CONTENT_HEIGHT / 1.250f + trumpY * trump[count]->GetScale().y * 1.150f);
		trump[count]->SetTurnFlag(false, count);
		trumpX += TRUMP_WIDTH;
		if ((count + 1) % 13 == 0 && count > 0)
		{
			trumpX = 0;
			trumpY += TRUMP_HEIGHT;
		}
		count++;
	}

	//シャッフル呼び出し
	trump[count - 1]->Shuffle(trump);

	return trump;
}

//トランプの柄配置
Trump **Trump::HandleCreate()
{
	register int count = 0;
	int trumpX = 0, trumpY = 0;
	static Trump *handle[52];
	while (count < TRUMP_MAX)
	{
		handle[count] = static_cast<Trump*>(Sprite::Create("Assets//TrumpHandle.png"));
		handle[count]->SetAnchorPoint(0, 0);
		handle[count]->SetScale(0.50f, 0.50f);
		count++;
	}
	return handle;
}

//シャッフル
void Trump::Shuffle(Trump **trump)
{
	//rand空回し
	srand(time(NULL));
	rand(); rand(); rand(); rand(); rand();rand(); rand(); rand(); rand(); rand();
	rand(); rand(); rand(); rand(); rand();rand(); rand(); rand(); rand(); rand();

	register int shuffleCount = 0, trumpNum = 0;
	Point work;
	while (shuffleCount < TRUMP_MAX)
	{
		trumpNum = rand() % TRUMP_MAX;
		work.pX = trump[shuffleCount]->GetPosition().x;
		work.pY = trump[shuffleCount]->GetPosition().y;
		trump[shuffleCount]->SetPosition(trump[trumpNum]->GetPosition());
		trump[trumpNum]->SetPosition(work.pX, work.pY);

		shuffleCount++;
	}
	shuffleCount = 0;
}

//クリック時のフラグ変更セッター
void Trump::SetTurnFlag(bool val, int trumpCount)
{
	turnFlg[trumpCount] = val;
}


//フラグのゲッター
bool Trump::GetTurnFlag(int trumpCount)
{
	return turnFlg[trumpCount];
}

//トランプ消去
void Trump::RemoveTrump(Trump **trump, int *clickNumber)
{
	trump[clickNumber[0]]->RemoveFromParent();
	trump[clickNumber[1]]->RemoveFromParent();
}
