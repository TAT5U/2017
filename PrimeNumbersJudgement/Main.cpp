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

	printf("数値を入力 : ");
	scanf("%d", &value);

	while (value <= 1)
	{
		printf("値が不正です!!\n");
		scanf("%d", &value);
	}

	if (isPrimeNumber(START_NUM, value))
	{
		printf("素数です!!\n");
	}
	else
	{
		printf("素数ではありません!!\n");
	}

	return 0;
}