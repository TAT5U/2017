#include "Star.h"
#include "MyGameEngine\RenderTarget.h"

Star::Star()
{
	renderTarget_ = new RenderTarget();
	rotateY_ = 0.0f;
}


Star::~Star()
{
}

void Star::Load()
{
	LPD3DXBUFFER error = 0;
	if (FAILED(D3DXCreateEffectFromFile(g.pDevice, "StarShader.hlsl", NULL, NULL, NULL, NULL, &starShader_, &error)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}

	Fbx::Load("Assets//Star.fbx");
	SetPosition(0.0f, 2.0f, -1.0f);
	SetShader(starShader_);
	SetShaderPass(0);
	renderTarget_->Load();

	
}

void Star::Update()
{
	rotateY_++;
	SetRotate(0.0f, rotateY_, 0.0f);
}

void Star::Draw()
{
	Fbx::Draw();

	renderTarget_->ChangeTarget();
	Fbx::Draw();
	renderTarget_->ReturnTarget();

	g.pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g.pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	renderTarget_->Draw();

	g.pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g.pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
