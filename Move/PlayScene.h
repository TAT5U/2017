#pragma once
#include "MyGameEngine\Scene.h"

#include<time.h>

class RenderTarget;
class PlayScene : public Scene
{
	Sprite* _redBall;
	Sprite* _blueBall;

	float time_ = 0.0;
public:
	PlayScene();
	~PlayScene();

	void Init()   override;
	void Update()   override;

	void Input()   override;
};