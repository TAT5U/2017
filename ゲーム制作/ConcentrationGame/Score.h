/*Score.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Label.h"
/********************************/


class Score : public Label
{
	//プレイヤーごとのスコア
	static int score[4];

public:

	Score();
	~Score();

	//スコアのセッターとゲッター
	void SetScore(int val, int count);
	int GetScore(int count);

	//スコアの初期化
	void InitializeScore(int count);
};