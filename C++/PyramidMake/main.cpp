/*2017-04-19
	狩野 達哉
		ピラミッドを表示するプログラム*/

#include<stdio.h>
int main(void)
{
	//段数、カウントの変数
	int StageNum = 0, i = 1, j = 1,k = 0;

	//表示
	printf("段数 : ");

	//段数を入力させる
	scanf("%d", &StageNum);

	//空白用の変数に段数を格納
	k = StageNum;

	//段数分ループ
	while (i<=StageNum)
	{

		//必要な空白を現在の段数から計算
		while (k-i>0)
		{
			//表示
			printf("　");

			//マイナスカウント
			k--;
		}

		//*の表示
		while (j<=i*2-1)
		{
			//表示
			printf("＊");

			//カウント
			j++;
		}
		//改行
		printf("\n");

		//それぞれの変数を初期値に戻す
		j = 1;
		k = StageNum;

		//カウント
		i++;
	}

	//正常終了
	return 0;
}