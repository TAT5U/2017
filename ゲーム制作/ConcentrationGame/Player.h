/*Player.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "Score.h"
/********************************/


class Player : public Score
{
	//定数
	static const int PLAYER_MAX = 4;

	//プレイヤー名
	static TCHAR name[4][128];

public:

	Player();
	~Player();

	//プレイヤー作成
	static Player **Create();

	//プレイヤーの名前とスコアを表示
	void PlayerScore(TCHAR *label, int count, Player *player);

	//プレイヤーのスコアをセット
	void SetPlayerScore(Player *player, int count);
};

