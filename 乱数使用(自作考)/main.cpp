#include<stdio.h>
#include<time.h>
int srnd(int key_up,int flg)
{
	time_t ti;
	struct tm *l;
	ti = time(NULL);
	l = localtime(&ti);
	int year = l->tm_year, mon = l->tm_mon, day = l->tm_mday, h = l->tm_hour, m = l->tm_min, s = l->tm_sec;
	int rnd = 0, rnd2 = 0;
	rnd = (year + mon * day*h * m * s) / 200;
	rnd2 = (year + mon * day*h * m * s) / 150;

	while (rnd>key_up&&rnd2>key_up)
	{
		if (rnd>key_up)
		{
			rnd = rnd - key_up;
		}
		if (rnd2>key_up)
		{
			rnd2 = rnd2 - key_up;
		}

	}
	if (flg==1)
	{
		return rnd;
	}
	if (flg==2)
	{
		return rnd2;
	}
}
int main()
{
	int x, y, key_up=200;
		x = srnd(key_up,1) % key_up;
		y = srnd(key_up,2) % key_up;
		printf("x=%d	y=%d\n", x,y);

	return 0;
}