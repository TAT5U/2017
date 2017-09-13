#include"Judge.h"
#include"Player.h"
#include<stdio.h>

//プレイヤーのインスタンス生成
player player1("aaaaa"), player2("bbbbb");

//コンストラクタ
judge::judge()
{
	i = NULL;
	p1 = NULL;
	p2 = NULL;
}

//デストラクタ
judge::~judge()
{

}

//ジャンケンの判定
void judge::Judgement(int pl1, int pl2)
{
	//勝ったほうに通達させる
	if (pl1>pl2)
	{
		//パー vs チョキ
		if (pl1 - pl2 >= 2)
		{
			printf("%sの勝ち!\n",player2.getName().c_str());
			player2.notifyResult(true);
		}

		//グー vs チョキorパー vs グー
		else
		{
			printf("%sの勝ち!\n",player1.getName().c_str());
			player1.notifyResult(true);
		}
	}
	else if (pl1<pl2)
	{
		//チョキ vs パー
		if (pl2 - pl1 >= 2)
		{
			printf("%sの勝ち!\n", player1.getName().c_str());
			player1.notifyResult(true);
		}

		//グー vs パーorチョキ vs グー
		else
		{
			printf("%sの勝ち!\n",player2.getName().c_str());
			player2.notifyResult(true);
		}
	}
	//引き分け
	else
	{
		printf("引き分け!\n");
	}
}

//最終結果の判定
void judge::WinnerJudge()
{
	printf("%d対%dで", player1.getWinCount(), player2.getWinCount());
	if (player1.getWinCount()>player2.getWinCount())
	{
		printf("%sの勝利!\n", player1.getName().c_str());
	}
	else if (player1.getWinCount()<player2.getWinCount())
	{
		printf("%sの勝利!\n", player2.getName().c_str());
	}
	else
	{
		printf("引き分け!\n");
	}
}

//ゲーム進行
void judge::Disp()
{
	printf("じゃんけんスタート!\n");
	while (i < 3)
	{
		printf("[%d回戦]\n", i + 1);

		//プレイヤー1の手を呼び出す
		p1 = player1.showHand();
		printf(" VS ");

		//プレイヤー2の手を呼び出す
		p2 = player2.showHand();

		//改行
		printf("\n");

		//ジャンケンの判定
		Judgement(p1, p2);

		//改行
		printf("\n");

		//勝負数カウント
		i++;
	}
	//改行
	printf("\n");

	//最終結果の判定
	WinnerJudge();
}