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

	printf("���l����� : ");
	scanf("%d", &value);

	while (value <= 1)
	{
		printf("�l���s���ł�!!\n");
		scanf("%d", &value);
	}

	if (isPrimeNumber(START_NUM, value))
	{
		printf("�f���ł�!!\n");
	}
	else
	{
		printf("�f���ł͂���܂���!!\n");
	}

	return 0;
}