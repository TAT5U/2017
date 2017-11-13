/*TitleScene.h*/

#pragma once
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"

#include "PlayScene.h"

class TitleScene : public Scene
{
	Sprite *backGround, *title;
	bool fadeFlg;
public:
	TitleScene();
	~TitleScene();

	void Init() override;
	void Update() override;
	void Input() override;
};