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

	//0�ɂȂ�܂ő�����
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
	printf("2�̐�������͂��Ă��������B\n");
	printf("1�� : ");
	scanf("%d", &x);
	printf("2�� : ");
	scanf("%d", &y);

	printf("�ő���񐔂� %d �ł�\n", EuclidJudgement(x, y));
	printf("�ŏ����{���� %d �ł�\n", x * y / EuclidJudgement(x, y));
	return 0;
}