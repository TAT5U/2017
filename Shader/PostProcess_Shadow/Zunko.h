#pragma once
#include "MyGameEngine\Fbx.h"

class Zunko : public Fbx
{
	float _rotateY;
public:
	Zunko();
	~Zunko();

	void Load();
	void Update() override;

	void Draw() override;
	CREATE_FUNC(Zunko);
};

