#pragma once
#include "Fbx.h"



class Shadow : public Fbx
{

public:
	Shadow();
	~Shadow();

	void DrawShadowMap(LPDIRECT3DTEXTURE9 renderTexture);

	D3DXMATRIX ShadowLightView();

	D3DXMATRIX ShadowUV();
};

