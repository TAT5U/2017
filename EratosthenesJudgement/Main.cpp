#include<stdio.h>

const int START_NUMBER = 2;
const int MAX_NUMBER = 98;

bool Judgement(int num, int val)
{
	if (num % val == 0 && num > START_NUMBER)
	{
		return false;
	}
	else if (val * val <= num)
	{
		return Judgement(num, val + 1);
	}
	return true;
}
int main(void)
{
	register int count = 0;
	bool numbers[MAX_NUMBER] = { true };

	while (count < MAX_NUMBER)
	{
		numbers[count] = Judgement(count + START_NUMBER, START_NUMBER);
		if (numbers[count])
		{
			printf("%d\n", count + START_NUMBER);
		}
		count++;
	}
	count = 0;
	return 0;
}