/*Score.h*/

#include<stdio.h>
#include<stdlib.h>
class Score
{
public:

	//ファイルポインタ
	FILE *fp;

	//スコア・ランク用変数
	int score =0 ,*rank = 0,Rank = 0,cnt = 0,i = 0;

	//work・フラグ用変数
	int work = 0, sortFlg = 0, k = 0;

	//スコア書き込み
	int SetScore(int x);

	//スコア読み出し
	int GetScore(int flg,int i2);

	//スコアソート
	void Sort();
};

