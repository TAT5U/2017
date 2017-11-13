/*Judge.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Node.h"
#include "Trump.h"
#include "Player.h"
/********************************/


class Judge
{
public:

	Judge();
	~Judge();

	//判定
	bool Judgement(int *clickNumber);

	//勝者判定
	int GetWinner(Player **player);
};

