/*Score.cpp*/

#include "Score.h"

//staticなので外部で宣言
int Score::score[4];

Score::Score()
{

}


Score::~Score()
{

}

//セッター
void Score::SetScore(int val, int count)
{
	score[count] += val;
}

//ゲッター
int Score::GetScore(int count)
{
	return score[count];
}

//スコアの初期化
void Score::InitializeScore(int count)
{
	score[count] = 0;
}