/*Trump.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Sprite.h"
#include<time.h>
/********************************/


class Trump : public Sprite
{

	//定数宣言
	static const int TRUMP_WIDTH = 100;
	static const int TRUMP_HEIGHT = 150;
	static const int TRUMP_MAX = 52;

	//クリック時のフラグ
	static bool turnFlg[52];

public:

	Trump();
	~Trump();

	//トランプ配置
	static Trump **Create();

	//トランプの柄配置
	static Trump **HandleCreate();

	//シャッフル
	void Shuffle(Trump **trump);

	//クリック時のフラグ変更セッター
	void SetTurnFlag(bool val, int trumpCount);

	//フラグのゲッター
	bool GetTurnFlag(int trumpCount);

	//トランプ消去
	static void RemoveTrump(Trump **trump, int *clickNumber);

};
