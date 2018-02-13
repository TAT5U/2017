#pragma once
#include "MyGameEngine\Fbx.h"

class RenderTarget;

class Star : public Fbx
{
	RenderTarget *renderTarget_;
	LPD3DXEFFECT starShader_;
	float rotateY_;

public:
	Star();
	~Star();

	void Update() override;
	void Load();
	void Draw() override;




	CREATE_FUNC(Star);
};

