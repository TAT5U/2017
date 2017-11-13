#include<stdio.h>

const int START_NUM = 2;

bool isPrimeNumber(int startNum, int val)
{
	if (val % startNum == 0 && val > 2)
	{
		return false;
	}
	else if (val == 2)
	{
		return true;
	}
	else
	{
		if (startNum <= val / 2)
		{
			return isPrimeNumber(startNum + 1, val);
		}
	}
	return true;
}

int main(void)
{
	unsigned int value = 0;

	printf("”’l‚ğ“ü—Í : ");
	scanf("%d", &value);

	while (value <= 1)
	{
		printf("’l‚ª•s³‚Å‚·!!\n");
		scanf("%d", &value);
	}

	if (isPrimeNumber(START_NUM, value))
	{
		printf("‘f”‚Å‚·!!\n");
	}
	else
	{
		printf("‘f”‚Å‚Í‚ ‚è‚Ü‚¹‚ñ!!\n");
	}

	return 0;
}