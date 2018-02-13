#pragma once
#include "MyGameEngine\Fbx.h"

class Water : public Fbx
{
	float _uvScroll;				//…–ÊƒXƒNƒ[ƒ‹
public:
	Water();
	~Water();
	void Load();
	void Update() override;

	CREATE_FUNC(Water);
};
