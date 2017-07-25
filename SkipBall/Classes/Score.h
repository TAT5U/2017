/*Score.h*/

#include<stdio.h>
#include<stdlib.h>
class Score
{
public:

	//ファイルポインタ
	FILE *fp;

	//スコア書き込み
	int SetScore(int x);

	//スコア読み出し
	int GetScore(int flg);
};

