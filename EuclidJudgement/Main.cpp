#include<stdio.h>

int EuclidJudgement(int a, int b)
{
	int val = 0;
	if (a < b)
	{
		int work = a;
		a = b;
		b = work;
	}

	//0になるまで続ける
	while (val = a % b)
	{
		a = b;
		b = val;
	}

	return b;
}

int main(void)
{
	int x = 0, y = 0;
	printf("2つの整数を入力してください。\n");
	printf("1つ目 : ");
	scanf("%d", &x);
	printf("2つ目 : ");
	scanf("%d", &y);

	printf("最大公約数は %d です\n", EuclidJudgement(x, y));
	printf("最小公倍数は %d です\n", x * y / EuclidJudgement(x, y));
	return 0;
}