/*Score.cpp*/

/*2017-06-01
	TAT5U
		スコア書き込み*/

#include "Score.h"

//スコア書き込み
int Score::SetScore(int x)
{
	//score.datを開く・なければ作成
	fp = fopen("data/score.dat", "ab");

	//エラーで終了
	if (fp == NULL)
	{
		exit(1);
	}
	
	//書き込み
	fwrite(&x, sizeof(x), 1, fp);

	//閉じる
	fclose(fp);
}
//スコア読み出し
int Score::GetScore(int flg)
{
	int score = 999, work = 0;
	//score.datを開く
	fp = fopen("data/score.dat", "rb");

	//エラーでNULLを返す
	if (fp == NULL)
	{
		return NULL;
	}
	//最後まで読み込み
	while (fread(&work, sizeof(work), 1, fp))
	{
		//1番早かったスコアをscoreに格納
		if (score>work&&work != 0)
		{
			score = work;
		}
	}
	//閉じる
	fclose(fp);

	//ハイスコアを返す
	if (flg==0)
	{
		return score;
	}

	//自分のスコアを返す
	else if (flg==1)
	{
		return work;
	}
}
