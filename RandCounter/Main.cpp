#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	srand(time(NULL));
	register int count = 0;
	int digitCount[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	while (count < 100)
	{
		int r = (rand() % 100) + (rand() % 100) / 2;

		printf("%d, ", r);
		count++;

		digitCount[(r / 10)]++;
	}
	count = 0;
	printf("\n\n");


	while (count < 10)
	{
		int grafCount = 0;
		int grafValue = digitCount[count];

		printf("%d0”Ô‘ä : ", count);
		while (grafCount < grafValue)
		{
			printf("*");
			grafCount++;
		}
		printf("\n");
		count++;
	}

	return 0;
}