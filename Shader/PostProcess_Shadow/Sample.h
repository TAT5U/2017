#pragma once
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Camera.h"

#include "Water.h"
#include "Zunko.h"
#include "Star.h"



class RenderTarget;

class Sample : public Scene
{
	RenderTarget *_renderTarget;

	Fbx*	_torus;
	Fbx*	_torusRed;
	Fbx*	_torusPhong;
	Fbx*	_torusNormal;
	Fbx*	_torusHalf;

	Water *_water;
	Zunko *_zunko;

	Star *_star;


	// エフェクト(シェーダー)
	LPD3DXEFFECT _shader;
	LPD3DXEFFECT _waterShader;


	//環境マッピング用
	LPD3DXEFFECT _envShader;

	LPD3DXEFFECT _toonShader;
	

	//キューブテクスチャ
	LPDIRECT3DCUBETEXTURE9 _cubeTexture;
	LPDIRECT3DTEXTURE9 _toonTexture;


public:
	Sample();
	~Sample();

	void Init()   override;
	void Update()   override;

	void Draw() override;
};