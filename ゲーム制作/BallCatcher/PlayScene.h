/*PlayScene.h*/

#pragma once
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
#include "GameOverScene.h"

class PlayScene : public Scene
{
	//Sprite変数 オブジェクト・カーソル・バックグラウンド
	Sprite **obj, *cursor, *backGround;

	//位置
	Point *pos, *objpos;

	//要素数・カウントの変数
	int n, i, *flg, score, cnt, *workflg, *spFlg, prevDigit;

	//オブジェクトの衝突範囲
	MyRect *objRect, cursorRect;

	//スコア・タイムラベル
	Label *scoreText, *startTimeText;

	//フラグ
	bool speedFlg, *spobjFlg, timeFlg;

	//開始時間
	float startTime;

	TCHAR text[128];
	TCHAR timeText[128];
	bool fadeFlg;

public:
	PlayScene();
	~PlayScene();

	void Init() override;
	void Update() override;
	void Input() override;

	//落下速度
	void FallObj();

	//オブジェクト設定
	void SetObj();

	//レベルアップ時
	void LvUpObj();
};