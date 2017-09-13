/*2017-05-12
	狩野 達哉
		ジャンケンプログラム*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Rps.h"

const int SCISSORS = 1;
const int STONE = 2;
const int PAPER = 3;

//コンストラクタ
Rps::Rps()
{
	p1 = 0, p2 = 0;
}

//擬似乱数生成関数
int Rps::GetRnd(int min, int max)
{
	static char flg;
	if (flg==0)
	{
		srand((unsigned int)time(NULL));
		flg = 1;
	}
	return min + (int)(rand()*(max - min + 1.0) / (1.0 + RAND_MAX));
}

//ジャンケンの判定
int Rps::Judge(int n, int m)
{
	if (n>m)
	{
		//パー vs チョキ
		if (n-m>=2)
		{
			p2++;
			Rps::p2Disp();
		}

		//グー vs チョキorパー vs グー
		else
		{
			p1++;
			Rps::p1Disp();
		}

	}
	else if (n<m)
	{
		//チョキ vs パー
		if (m-n>=2)
		{
			p1++;
			Rps::p1Disp();
		}

		//グー vs パーorチョキ vs グー
		else
		{
			p2++;
			Rps::p2Disp();
		}
	}
	//引き分け
	else
	{
		Rps::p1p2Disp();
	}
	return 0;
}

//ジャンケンの表示
int Rps::JudgeDisp(int n)
{
	if (n==SCISSORS)
	{
		printf("チョキ");
	}
	else if (n==STONE)
	{
		printf("グー");
	}
	else
	{
		printf("パー");
	}
	return 0;
}

//プレイヤー1の勝利時の表示
void Rps::p1Disp()
{
	printf("プレイヤー1の勝ち!\n");
}

//プレイヤー2の勝利時の表示
void Rps::p2Disp()
{
	printf("プレイヤー2の勝ち!\n");
}

//引き分けの際に表示
void Rps::p1p2Disp()
{
	printf("引き分け!\n");
}

//3回勝負した結果を表示
void Rps::Disp()
{
	printf("%d対%dで",p1,p2);
	if (p1>p2)
	{
		Rps::p1Disp();
	}
	else if (p1<p2)
	{
		Rps::p2Disp();
	}
	else
	{
		Rps::p1p2Disp();
	}
}

//メイン関数
int main(void)
{
	int i = 0, p1s = 0, p2s = 0;
	Rps rps;
	printf("じゃんけんスタート!\n");
	while (i<3)
	{
		printf("[%d回戦]\n", i + 1);

		//プレイヤー1の手選択
		p1s = rps.GetRnd(SCISSORS,PAPER);
		
		//手の表示
		rps.JudgeDisp(p1s);
		printf(" VS ");

		//プレイヤー2の手選択
		p2s = rps.GetRnd(SCISSORS, PAPER);

		//手の表示
		rps.JudgeDisp(p2s);

		//改行
		printf("\n");

		//ジャンケンの判定
		rps.Judge(p1s, p2s);

		//改行
		printf("\n");

		//カウント
		i++;
	}

	//結果表示
	rps.Disp();

	//正常終了
	return 0;
}