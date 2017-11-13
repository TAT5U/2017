/*Judge.cpp*/

#include "Judge.h"



Judge::Judge()
{
}


Judge::~Judge()
{
}

//”»’è
bool Judge::Judgement(int *clickNumber)
{
	if (clickNumber[0] % 13 == clickNumber[1] % 13)
	{
		return true;
	}
	return false;
}

//ŸÒ”»’è
int Judge::GetWinner(Player **player)
{
	int count = 0, win = 0, winerScore = 0;
	while (count < 4)
	{
		if (winerScore < player[count]->GetScore(count))
		{
			winerScore = player[count]->GetScore(count);
			win = count;
		}
		count++;
	}

	return win + 1;
}