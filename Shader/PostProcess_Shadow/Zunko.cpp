#include "Zunko.h"


Zunko::Zunko()
{
	_rotateY = 0.0f;
}


Zunko::~Zunko()
{
}

void Zunko::Load()
{
	Fbx::Load("Assets//Zun//zunko.fbx");
}

void Zunko::Update()
{
	_rotateY++;
	SetRotate(0, _rotateY, 0);
}

void Zunko::Draw()
{
	g.pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	SetShaderPass(1);
	Fbx::Draw();

	g.pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	SetShaderPass(0);
	Fbx::Draw();
}
