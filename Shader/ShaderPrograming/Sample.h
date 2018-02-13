#pragma once
#include "MyGameEngine\Scene.h"

class Sample : public Scene
{
	Fbx *tours;
public:
	Sample();
	~Sample();
	void Init() override;
	void Update() override;
	void Input() override;
};

