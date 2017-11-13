#include<stdio.h>

const int LOOP_MAX = 100;

bool FizzJudge(int val)
{
	if (val % 3 == 0)
	{
		return true;
	}
	return false;
}

bool BuzzJudge(int val)
{
	if (val % 5 == 0)
	{
		return true;
	}
	return false;
}


int main(void)
{
	register unsigned int count = 1;
	bool isFizz = false, isBuzz = false;

	while (count <= LOOP_MAX)
	{
		isFizz = FizzJudge(count);
		isBuzz = BuzzJudge(count);

		if (!isFizz && !isBuzz)
		{
			printf("%d", count);
		}
		if (isFizz)
		{
			printf("Fizz");
		}
		if (isBuzz)
		{
			printf("Buzz");
		}

		printf("\n");
		
		count++;
	}
	count = 0;

	return 0;
}