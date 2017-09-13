#include"Player.h"
#include<stdio.h>

//乱数を使用するためのヘッダ
#include<stdlib.h>
#include<time.h>

const int SCISSORS = 1;
const int STONE = 2;
const int PAPER = 3;

//コンストラクタ	
player::player(string _name)
{
	name = _name;
	n = NULL;
	winCount = NULL;
}

//デストラクタ
player::~player()
{

}

//手を出す
int player::showHand()
{
	//擬似乱数で取得
	n = GetRnd(SCISSORS, PAPER);

	if (n == SCISSORS)
	{
		printf("チョキ");
	}
	else if (n == STONE)
	{
		printf("グー");
	}
	else
	{
		printf("パー");
	}
	return n;
}

//自分の勝ち数を答える
int player::getWinCount()
{
	return winCount;
}

//勝ったときに審判から結果をもらう
void player::notifyResult(bool result)
{
	//勝ち数カウント
	winCount++;
}

//擬似乱数生成関数
int player::GetRnd(int min, int max)
{
	static char flg;
	if (flg == 0)
	{
		srand((unsigned int)time(NULL));
		flg = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}
string player::getName()
{
	return name;
}