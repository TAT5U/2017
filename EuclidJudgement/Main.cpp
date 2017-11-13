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

	//0‚É‚È‚é‚Ü‚Å‘±‚¯‚é
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
	printf("2‚Â‚Ì®”‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B\n");
	printf("1‚Â–Ú : ");
	scanf("%d", &x);
	printf("2‚Â–Ú : ");
	scanf("%d", &y);

	printf("Å‘åŒö–ñ”‚Í %d ‚Å‚·\n", EuclidJudgement(x, y));
	printf("Å¬Œö”{”‚Í %d ‚Å‚·\n", x * y / EuclidJudgement(x, y));
	return 0;
}