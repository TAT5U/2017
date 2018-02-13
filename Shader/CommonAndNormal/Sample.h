#pragma once
#include "MyGameEngine\Scene.h"

class Sample : public Scene
{
	Fbx*	_torus;
	Fbx*	_torusRed;
	Fbx*	_torusPhong;
	Fbx*	_torusNormal;
	Fbx*	_torusHalf;

	// �G�t�F�N�g(�V�F�[�_�[)
	LPD3DXEFFECT _shader;
	LPD3DXEFFECT _waterShader;


public:
	Sample();
	~Sample();

	void Init()   override;
	void Update()   override;
};