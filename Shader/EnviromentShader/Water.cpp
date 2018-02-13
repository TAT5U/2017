#include "Water.h"


Water::Water()
{
	_uvScroll = 0.0f;
}


Water::~Water()
{
}

void Water::Load()
{
	Fbx::Load("Assets\\Water.fbx");
}
void Water::Update()
{
	_uvScroll += 0.001f;
	_shader->SetFloat("uvScroll", _uvScroll);
}
