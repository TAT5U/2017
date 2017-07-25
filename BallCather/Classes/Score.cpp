#include "Score.h"

//スコア書き込み
int Score::SetScore(int x)
{
	//score.datを開く・なければ作成
	fp = fopen("score.dat", "ab");

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
int Score::GetScore(int flg,int i2)
{
	//変数初期化
	cnt = 0;
	i = 0;

	//score.datを開く
	fp = fopen("score.dat", "rb");

	//エラーで終了
	if (fp == NULL)
	{
		exit(1);
	}
	
	//書き込まれているスコアの総数をカウント
	while (fread(&score, sizeof(score), 1, fp))
	{
		cnt++;
	}

	//閉じる
	fclose(fp);

	//自分のスコアだけ読み出し
	if (flg == 0)
	{
		return score;
	}

	//動的配列作成
	rank = new int[cnt];

	//score.datを開
	fp = fopen("score.dat", "rb");

	//エラーで終了
	if (fp == NULL)
	{
		exit(1);
	}

	//書き込まれているスコアを読み出し
	while (fread(&rank[i], sizeof(rank[i]), 1, fp))
	{
		i++;
	}

	//ソートを実行
	Sort();

	//閉じる
	fclose(fp);

	//自分の順位だけ読み出し
	if (flg==1)
	{
		i = 0;
		while (i<cnt)
		{
			//自分の順位を探す
			if (rank[i] == score)
			{
				delete[]rank;
				return i+1;
			}
			i++;
		}
	}

	//上位のスコアを読み出し
	else if (flg==2)
	{
		//解放させるため
		Rank = rank[i2];
		delete[]rank;
		return Rank;
	}

	//10位以上スコアが入ってないかどうか
	else if (flg==3)
	{
		delete[]rank;
		return cnt;
	}
}
//スコアソート
void Score::Sort()
{
	//変数初期化
	k = 0;
	i = 0;

	//バブルソートで入れ替え
	do
	{
		sortFlg = 0;
		while (i < cnt - 1 - k)
		{
			if (rank[i] < rank[i + 1])
			{
				sortFlg = 1;
				work = rank[i];
				rank[i] = rank[i + 1];
				rank[i + 1] = work;
			}
			i++;
		}
		i = 0;
		k++;
	} while (sortFlg == 1);
}
