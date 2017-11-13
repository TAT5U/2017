/*TitleScene.h*/

//インクルードガード
#pragma once

/**********インクルード**********/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"

#include "BackGround.h"
#include "PlayScene.h"
/********************************/


class TitleScene : public Scene
{
	//背景
	BackGround *backGround;

	//タイトル
	Sprite *title;

	//フェードフラグ
	bool fadeFlg;

public:

	TitleScene();
	~TitleScene();

	void Init() override;
	void Update() override;
	void Input() override;
};