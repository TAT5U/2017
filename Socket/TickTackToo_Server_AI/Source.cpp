/*2017-09-11
	狩野 達哉
		サーバサンプルプログラム*/

/*****インクルード*****/
#include<stdio.h>
#include<winsock2.h>
#include<conio.h>
#include<iostream>
#include<cctype>
#include<time.h>
/**********************/

/**************リンカ**************/
#pragma comment(lib,"wsock32.lib")
/**********************************/
#define GET_ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

int frame[3][3] = { 0 };
SOCKET sock;

void DispTickTack(int i, int j)
{
	if (frame[i][j] == 0)
	{
		printf("|　");
	}
	else if (frame[i][j] == 1)
	{
		printf("|○");
	}
	else if (frame[i][j] == -1)
	{
		printf("|×");
	}


	if (i >= 2)
	{
		printf("|\n");
	}
}

int Judge()
{
	// 横
	if ((frame[0][0] + frame[1][0] + frame[2][0] == 3) || (frame[0][1] + frame[1][1] + frame[2][1] == 3) || (frame[0][2] + frame[1][2] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[1][0] + frame[2][0] == -3) || (frame[0][1] + frame[1][1] + frame[2][1] == -3) || (frame[0][2] + frame[1][2] + frame[2][2] == -3))
	{
		return -1;
	}

	// 縦
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == 3) || (frame[1][0] + frame[1][1] + frame[1][2] == 3) || (frame[2][0] + frame[2][1] + frame[2][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[0][1] + frame[0][2] == -3) || (frame[1][0] + frame[1][1] + frame[1][2] == -3) || (frame[2][0] + frame[2][1] + frame[2][2] == -3))
	{
		return -1;
	}

	// 斜め
	// *   *
	//   *
	// *   *
	else if ((frame[0][0] + frame[1][1] + frame[2][2] == 3) || (frame[2][0] + frame[1][1] + frame[0][2] == 3))
	{
		return 1;
	}
	else if ((frame[0][0] + frame[1][1] + frame[2][2] == -3) || (frame[2][0] + frame[1][1] + frame[0][2] == -3))
	{
		return -1;
	}

	return 0;
}

void SimpleAI(int i)
{
	int p;
	int q;
	int cnt = 0, cnt2 = 0;
	int tag = 0, tag2 = 0;
	int AIinputX = 0, AIinputY = 0;
	char AImes[256] = { 0 }, AImes2[256] = { 0 };
	char AIsend[256] = { 0 };
	bool flg = false;

	if (i <= 0)
	{
		p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
		q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));

		// X
		if (p == 0)
		{
			sprintf(AImes, "%d", p);
		}
		else if (p == 1)
		{
			sprintf(AImes, "%d", p);
		}
		else if (p == 2)
		{
			sprintf(AImes, "%d", p);
		}

		// Y
		if (q == 0)
		{
			sprintf(AImes2, "%d", q);
		}
		else if (q == 1)
		{
			sprintf(AImes2, "%d", q);
		}
		else if (q == 2)
		{
			sprintf(AImes2, "%d", q);
		}

		AIinputX = *AImes - '0';
		AIinputY = *AImes2 - '0';

		while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2 || q > 2)
		{
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));

			// X
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			// Y
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';
		}
	}
	else
	{















		// 横+
		while (cnt2 < 3)
		{
			if (frame[cnt][cnt2] + frame[cnt + 1][cnt2] + frame[cnt + 2][cnt2] == 2)
			{
				tag = cnt2;
				flg = true;
			}
			cnt2++;
		}

		// CPU
		p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
		if (p == 0)
		{
			sprintf(AImes, "%d", p);
		}
		else if (p == 1)
		{
			sprintf(AImes, "%d", p);
		}
		else if (p == 2)
		{
			sprintf(AImes, "%d", p);
		}

		q = tag;
		sprintf(AImes2, "%d", q);

		AIinputX = *AImes - '0';
		AIinputY = *AImes2 - '0';

		// CPU
		while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2)
		{
			if (frame[0][tag] != 0 && frame[1][tag] != 0 && frame[2][tag] != 0)
			{
				flg = false;
				break;
			}
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			q = tag;

			sprintf(AImes2, "%d", q);

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';
		}
		cnt2 = 0;
		if (flg == false)
		{

			while (cnt < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt][cnt2 + 1] + frame[cnt][cnt2 + 2] == 2)
				{
					tag = cnt;
					flg = true;
				}
				cnt++;
			}

			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			sprintf(AImes, "%d", p);
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || q > 2)
			{
				//printf("222");
				if (frame[tag][0] != 0 && frame[tag][1] != 0 && frame[tag][2] != 0)
				{
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				sprintf(AImes, "%d", p);
				if (q == 0)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 1)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 2)
				{
					sprintf(AImes2, "%d", q);
				}

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		//printf("%d", cnt);
		cnt = 0;

		if (flg == false)
		{
			//	斜め+
			if (frame[cnt][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt + 2][cnt2 + 2] == 2)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[0][0] != 0 && frame[1][1] != 0 && frame[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{

			//	斜め2+
			if (frame[cnt + 2][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt][cnt2 + 2] == 2)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[2][0] != 0 && frame[1][1] != 0 && frame[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;







		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt + 1][cnt2] + frame[cnt + 2][cnt2] == -2)
				{
					//printf("aaaaaa");
					tag = cnt2;
					flg = true;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			q = tag;
			sprintf(AImes2, "%d", q);

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frame[0][tag] != 0 && frame[1][tag] != 0 && frame[2][tag] != 0)
				{
					flg = false;
					break;
				}
				//printf("11");
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				if (p == 0)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 1)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 2)
				{
					sprintf(AImes, "%d", p);
				}

				q = tag;

				sprintf(AImes2, "%d", q);

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt2 = 0;
		if (flg == false)
		{

			while (cnt < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt][cnt2 + 1] + frame[cnt][cnt2 + 2] == -2)
				{
					//printf("bbbbbb");
					tag = cnt;
					flg = true;
				}
				cnt++;
			}

			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			sprintf(AImes, "%d", p);
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || q > 2)
			{
				//printf("222");
				if (frame[tag][0] != 0 && frame[tag][1] != 0 && frame[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				sprintf(AImes, "%d", p);
				if (q == 0)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 1)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 2)
				{
					sprintf(AImes2, "%d", q);
				}

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		//printf("%d", cnt);
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frame[cnt][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt + 2][cnt2 + 2] == -2)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[0][0] != 0 && frame[1][1] != 0 && frame[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{

			//	斜め2
			if (frame[cnt + 2][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt][cnt2 + 2] == -2)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[2][0] != 0 && frame[1][1] != 0 && frame[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;



		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt + 1][cnt2] + frame[cnt + 2][cnt2] == 1)
				{
					//printf("aaaaaa");
					tag = cnt2;
					flg = true;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			q = tag;
			sprintf(AImes2, "%d", q);

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frame[0][tag] != 0 && frame[1][tag] != 0 && frame[2][tag] != 0)
				{
					flg = false;
					break;
				}
				//printf("11");
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				if (p == 0)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 1)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 2)
				{
					sprintf(AImes, "%d", p);
				}

				q = tag;

				sprintf(AImes2, "%d", q);

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt2 = 0;
		if (flg == false)
		{

			while (cnt < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt][cnt2 + 1] + frame[cnt][cnt2 + 2] == 1)
				{
					//printf("bbbbbb");
					tag = cnt;
					flg = true;
				}
				cnt++;
			}

			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			sprintf(AImes, "%d", p);
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || q > 2)
			{
				//printf("222");
				if (frame[tag][0] != 0 && frame[tag][1] != 0 && frame[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				sprintf(AImes, "%d", p);
				if (q == 0)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 1)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 2)
				{
					sprintf(AImes2, "%d", q);
				}

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		//printf("%d", cnt);
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frame[cnt][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt + 2][cnt2 + 2] == 1)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[0][0] != 0 && frame[1][1] != 0 && frame[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{

			//	斜め2
			if (frame[cnt + 2][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt][cnt2 + 2] == 1)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[2][0] != 0 && frame[1][1] != 0 && frame[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;



		if (flg == false)
		{
			// 横
			while (cnt2 < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt + 1][cnt2] + frame[cnt + 2][cnt2] == -1)
				{
					//printf("aaaaaa");
					tag = cnt2;
					flg = true;
				}
				cnt2++;
			}

			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			q = tag;
			sprintf(AImes2, "%d", q);

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2)
			{
				if (frame[0][tag] != 0 && frame[1][tag] != 0 && frame[2][tag] != 0)
				{
					flg = false;
					break;
				}
				//printf("11");
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				if (p == 0)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 1)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 2)
				{
					sprintf(AImes, "%d", p);
				}

				q = tag;

				sprintf(AImes2, "%d", q);

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt2 = 0;
		if (flg == false)
		{

			while (cnt < 3)
			{
				if (frame[cnt][cnt2] + frame[cnt][cnt2 + 1] + frame[cnt][cnt2 + 2] == -1)
				{
					//printf("bbbbbb");
					tag = cnt;
					flg = true;
				}
				cnt++;
			}

			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			p = tag;
			sprintf(AImes, "%d", p);
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || q > 2)
			{
				//printf("222");
				if (frame[tag][0] != 0 && frame[tag][1] != 0 && frame[tag][2] != 0)
				{
					flg = false;
					break;
				}
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				p = tag;
				sprintf(AImes, "%d", p);
				if (q == 0)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 1)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 2)
				{
					sprintf(AImes2, "%d", q);
				}

				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		//printf("%d", cnt);
		cnt = 0;

		if (flg == false)
		{
			//	斜め
			if (frame[cnt][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt + 2][cnt2 + 2] == -1)
			{
				tag = cnt;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[0][0] != 0 && frame[1][1] != 0 && frame[2][2] != 0)
				{
					flg = false;
					break;
				}
				tag++;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;
		if (flg == false)
		{

			//	斜め2
			if (frame[cnt + 2][cnt] + frame[cnt + 1][cnt2 + 1] + frame[cnt][cnt2 + 2] == -1)
			{
				tag = cnt + 2;
				tag2 = cnt2;
				flg = true;
			}
			p = tag;
			q = tag2;

			sprintf(AImes, "%d", p);
			sprintf(AImes2, "%d", q);


			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0)
			{
				if (frame[2][0] != 0 && frame[1][1] != 0 && frame[0][2] != 0)
				{
					flg = false;
					break;
				}
				tag--;
				tag2++;

				p = tag;
				q = tag2;

				sprintf(AImes, "%d", p);
				sprintf(AImes2, "%d", q);


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
		cnt = 0;
		cnt2 = 0;

		if (flg == false)
		{
			// CPU
			p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
			if (p == 0)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 1)
			{
				sprintf(AImes, "%d", p);
			}
			else if (p == 2)
			{
				sprintf(AImes, "%d", p);
			}

			// CPU
			if (q == 0)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 1)
			{
				sprintf(AImes2, "%d", q);
			}
			else if (q == 2)
			{
				sprintf(AImes2, "%d", q);
			}

			AIinputX = *AImes - '0';
			AIinputY = *AImes2 - '0';

			// CPU
			while (AIinputX > 2 || AIinputY > 2 || frame[AIinputX][AIinputY] != 0 || p > 2 || q > 2)
			{

				// CPU
				p = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				q = 0 + (int)(rand()*(2 - 0 + 1.0) / (1.0 + RAND_MAX));
				if (p == 0)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 1)
				{
					sprintf(AImes, "%d", p);
				}
				else if (p == 2)
				{
					sprintf(AImes, "%d", p);
				}

				// CPU
				if (q == 0)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 1)
				{
					sprintf(AImes2, "%d", q);
				}
				else if (q == 2)
				{
					sprintf(AImes2, "%d", q);
				}


				AIinputX = *AImes - '0';
				AIinputY = *AImes2 - '0';
			}
		}
	}

	frame[AIinputX][AIinputY] = 1;
	strcpy(AIsend, AImes);
	strcat(AIsend, ",");
	strcat(AIsend, AImes2);

	// 送る
	if (send(sock, AIsend, strlen(AIsend), 0) < 0)
	{
		//エラー処理
		fprintf(stderr, "sendエラー\n");
		exit(1);
	}
}


int main(void)
{
	//変数を宣言
	char key;
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int mesSize, mesSize2, mesMax;
	int x = 0, y = 0;
	int playCount = 0;
	char sendmes[256] = { 0 };

	// 乱数空回し(CPU)
	srand(time(NULL));
	rand(); rand(); rand(); rand(); rand(); rand(); rand(); rand(); rand(); rand();

	//起動時
	printf("サーバ起動中・・・\n");

	//winsock2(Windows Sockketの略)の初期化
	int status = WSAStartup(MAKEWORD(2, 0), &wsaData);

	//エラー処理
	if (status != 0)
	{
		//仕事で組むなら考慮する必要がある
		switch (status)
		{
			//準備されていない
		case WSASYSNOTREADY:
			break;

			//バージョンが違う
		case WSAVERNOTSUPPORTED:
			break;

			//通信がブロックされている
		case WSAEINPROGRESS:
			break;

			//多重起動されている
		case WSAEPROCLIM:
			break;
		}
	}

	//ソケットの作成
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET)
	{
		//エラー処理
		fprintf(stderr, "socketエラー\n");
		exit(1);
	}

	//ソケットの設定
	//IPアドレス(IPv4)
	addr.sin_family = AF_INET;

	//ポート番号	ウェルノウンポートと被らない番号
	addr.sin_port = htons(12345);

	//通信相手とするクライアントのアドレス制限
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	//ソケットとローカル受付のポート番号の関連付けを行う
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		//エラー処理
		fprintf(stderr, "bindエラー\n");
		exit(1);
	}
	while (1)
	{
		//TCPクライアントからの接続要求を待てる状態にする
		if (listen(sock0, 5) < 0)
		{
			//エラー処理
			fprintf(stderr, "listenエラー\n");
			exit(1);
		}


		//TCPクライアントからの接続要求を受け付ける
		len = sizeof(client);

		//クライアント起動を要求
		printf("クライアントを起動してください\n");

		//ソケットのlistenを設定した後に保留中の接続要求を受け入れる
		sock = accept(sock0, (struct sockaddr *)&client, &len);
		if (sock < 0)
		{
			//エラー処理
			fprintf(stderr, "acceptエラー\n");
			exit(1);
		}

		//起動成功時
		printf("起動成功!\n");

		//表示
		printf("～～～三目並べ～～～\n\n");

		while (1)
		{
			int judge;
			char recvbuf[256];

			//終了判断の変数
			int inputX = 0, inputY = 0;

			//送信するメッセージの変数
			char mes[256] = { 0 }, mes2[256] = { 0 };


			SimpleAI(playCount);


			printf("      0  1  2  \n");
			while (y < 3)
			{
				printf("    -----------\n");
				printf(" %d  ", y);
				while (x < 3)
				{
					DispTickTack(x, y);
					x++;
				}
				x = 0;
				y++;
			}
			printf("    -----------\n");
			x = 0;
			y = 0;
			printf("\n");
			playCount++;
			judge = Judge();
			if (judge == 1)
			{
				printf("勝ち!\n");
				exit(1);
			}
			else if (judge == -1)
			{
				printf("負け!\n");
				exit(1);
			}

			if (playCount >= 9)
			{
				printf("引き分け!\n");
				exit(1);
			}

			//サーバからデータを受信
			memset(&recvbuf, 0, 256);

			//メッセージ受け取り
			int n = recv(sock, recvbuf, sizeof(recvbuf), 0);
			if (n < 0)
			{
				//エラー処理
				fprintf(stderr, "recvエラー\n");
				exit(1);
			}

			inputX = *(strtok(recvbuf, ",")) - '0';
			inputY = *(strtok(NULL, ",")) - '0';
			frame[inputX][inputY] = -1;

			printf("      0  1  2  \n");
			while (y < 3)
			{
				printf("    -----------\n");
				printf(" %d  ", y);
				while (x < 3)
				{
					DispTickTack(x, y);
					x++;
				}
				x = 0;
				y++;
			}
			printf("    -----------\n");
			x = 0;
			y = 0;
			printf("\n");

			playCount++;
			judge = Judge();
			if (judge == 1)
			{
				printf("勝ち!\n");
				exit(1);
			}
			else if (judge == -1)
			{
				printf("負け!\n");
				exit(1);
			}

			if (playCount >= 9)
			{
				printf("引き分け!\n");
				exit(1);
			}
		}
	}

	//TCPセッションの終了
	closesocket(sock);

	//記述しなければメモリリークになってしまうため必須
	//winsock2の終了処理
	WSACleanup();

	//正常終了
	return 0;
}

