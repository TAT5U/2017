/*2017-04-19
狩野 達哉
	ピラミッドを表示するプログラム
				矢印キーで回転させる*/

#include<stdio.h>

//systemコマンドを使用するためのヘッダ
#include <stdlib.h>

//getchを使用するためのヘッダ
#include<conio.h>

int main(void)
{
	//段数、カウントの変数
	int StageNum = 0, i = 1, j = 1, k = 0, key = 0, HNum = 0, cnt = 0;

	//キーが押されたときのフラグ
	bool flgU = false, flgD = false, flgR = false, flgL = false;

	//表示
	printf("段数 : ");

	//段数を入力させる
	scanf("%d", &StageNum);

	//空白用の変数に段数を格納
	k = StageNum;

	//段数分ループ
	while (i <= StageNum)
	{
		//必要な空白を現在の段数から計算
		while (k - i>0)
		{
			//空白表示
			printf("　");

			//空白用の変数マイナスカウント
			k--;
		}

		//*の表示
		while (j <= i * 2 - 1)
		{
			//表示
			printf("＊");

			//最後の段の数をカウント
			if (i==StageNum)
			{
				cnt++;
			}
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

	//キー入力(矢印)で回転&Escで終了
	while (1)
	{
		//キー入力
		key = getch();

		//矢印キーは特殊で2バイトのコードになる
		//矢印かどうかの確認
		if (key==0xe0)
		{
			//もう一度格納
			key = getch();

			//→が押されたときは右に回転したピラミッド表示
			if (key == 0x4d)
			{
				//→が押され続けていなければ
				if (flgR==false)
				{
					//表示を1度消す
					system("cls");

					//表示
					printf("段数 : %d\n", StageNum);

					//フラグの変更
					flgR = true;
					flgD = false;
					flgL = false;
					flgU = false;

					//段数の変数を初期値に戻す
					i = 1, j = 1;

					//回転したピラミッドの上半分の段数を格納
					HNum = cnt / 2;

					//上半分のループ
					while (i <= HNum + 1)
					{
						//*の表示
						while (j <= i)
						{
							//表示
							printf("＊");

							//カウント
							j++;
						}

						//改行
						printf("\n");

						//変数を初期値に戻す
						j = 1;

						//カウント
						i++;
					}

					//下半分の段数を格納&初期値に戻す
					i = HNum;
					j = 1;

					//下半分のループ
					while (i > 0)
					{
						//*の表示
						while (j <= i)
						{
							//表示
							printf("＊");

							//カウント
							j++;
						}

						//改行
						printf("\n");

						//変数を初期値に戻す
						j = 1;

						//マイナスカウント
						i--;
					}
				}

			}

			//↓が押されたときは下に回転したピラミッド表示
			else if (key == 0x50)
			{
				//↓が押され続けていなければ
				if (flgD==false)
				{
					//表示を1度消す
					system("cls");

					//表示
					printf("段数 : %d\n", StageNum);

					//フラグの変更
					flgR = false;
					flgD = true;
					flgL = false;
					flgU = false;

					//段数、カウントの変数
					i = 0, j = 0, k = 1;

					//段数分ループ
					while (i <= StageNum)
					{
						//空白の表示
						while (k <= i)
						{
							//空白表示
							printf("　");

							//空白用の変数カウント
							k++;
						}

						//*の表示
						while (j <= StageNum * 2 - i * 2 - 2)
						{
							//表示
							printf("＊");

							//カウント
							j++;
						}

						//改行
						printf("\n");

						//それぞれの変数を初期値に戻す
						j = 0;
						k = 1;

						//カウント
						i++;
					}
				}
				
			}

			//←が押されたときは左に回転したピラミッド表示
			else if (key == 0x4b)
			{
				//←が押され続けていなければ
				if (flgL==false)
				{
					//表示を1度消す
					system("cls");

					//表示
					printf("段数 : %d\n", StageNum);

					//フラグの変更
					flgR = false;
					flgD = false;
					flgL = true;
					flgU = false;

					//段数、カウントの変数
					i = 1, j = 1, k = 0;

					//回転したピラミッドの上半分の段数を格納
					HNum = cnt / 2;

					//上半分のループ
					while (i <= HNum + 1)
					{
						//空白の表示
						while (k <= HNum - i)
						{
							//空白表示
							printf("　");

							//空白用の変数カウント
							k++;
						}

						//*の表示
						while (j <= i)
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
						k = 0;

						//カウント
						i++;
					}

					//それぞれの変数を初期値に戻す
					i = 1;
					j = 1;
					k = 0;

					//下半分のループ
					while (i <= HNum)
					{
						//空白の表示
						while (k <= i - 1)
						{
							//空白表示
							printf("　");

							//空白用の変数カウント
							k++;
						}
						//*の表示
						while (j <= HNum - i + 1)
						{
							//表示
							printf("＊");

							//カウント
							j++;
						}

						//改行
						printf("\n");

						//それぞれの変数を初期値に戻す
						k = 0;
						j = 1;

						//カウント
						i++;
					}
				}
				
			}

			//↑が押されたときは元の向きのピラミッド表示
			else if (key == 0x48)
			{
				//↑が押され続けていなければ
				if (flgU==false)
				{
					//表示を1度消す
					system("cls");

					//表示
					printf("段数 : %d\n", StageNum);

					//フラグの変更
					flgR = false;
					flgD = false;
					flgL = false;
					flgU = true;

					//段数、カウントの変数
					i = 1, j = 1, cnt = 0;

					//空白用の変数に段数を格納
					k = StageNum;

					//段数分ループ
					while (i <= StageNum)
					{
						//必要な空白を現在の段数から計算
						while (k - i>0)
						{
							//表示
							printf("　");

							//マイナスカウント
							k--;
						}

						//*の表示
						while (j <= i * 2 - 1)
						{
							//表示
							printf("＊");
							if (i == StageNum)
							{
								cnt++;
							}
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
				}
				
			}
		}
		//Escが入力されたら終了
		else if (key == 27)
		{
			break;
		}
	}

	//正常終了
	return 0;
}
