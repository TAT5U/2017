#include<stdio.h>
enum TickTack
{
	None = 1,
	Circle = 2,
	Xmark = 3
};

int frame[3][3] = {0};

void DispTickTack(int i, int j)
{
	if (frame[i][j] == 0)
	{
		printf("@");
	}
	else if (frame[i][j] == 1)
	{
		printf("›");
	}
	else
	{
		printf("~");
	}


	if (i >= 2)
	{
		printf("\n");
	}
}

int main(void)
{
	int x = 0, y = 0;
	int inputX = 0, inputY = 0;
	bool playerFlg = false;

	printf("```O–Ú•À‚×```\n\n");
	while (true)
	{

		if (scanf("%d %d", &inputX, &inputY),inputX > 2||inputY > 2)
		{
			printf("À•W‚ª•s³!!\n");
			continue;
		}
		if (!playerFlg)
		{
			frame[inputX][inputY] = 1;
			playerFlg = true;
		}
		else
		{
			frame[inputX][inputY] = 2;
			playerFlg = false;
		}

		while (y < 3)
		{
			while (x < 3)
			{
				DispTickTack(x, y);
				x++;
			}
			x = 0;
			y++;
		}
		x = 0;
		y = 0;
		printf("\n");
	}



}

