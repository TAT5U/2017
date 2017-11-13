/*GameOverScene.h*/

#pragma once
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"

class GameOverScene : public Scene
{
	Sprite *backGround, *gameOver, *retry, *end;
	bool fadeFlg;
public:
	GameOverScene();
	~GameOverScene();

	void Init() override;
	void Update() override;
	void Input() override;
};