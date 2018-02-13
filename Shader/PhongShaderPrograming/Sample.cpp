#include "Sample.h"


Sample::Sample()
{
	tours_ = nullptr;
}


Sample::~Sample()
{
}

void Sample::Init()
{
	//ƒ‰ƒCƒgì¬
	Light *light = Light::Create();
	AddChild(light);

	tours_ = Fbx::Create("Assets//Torus.fbx");
	AddChild(tours_);
}
void Sample::Update()
{
	tours_->SetRotate(tours_->GetRotate() + D3DXVECTOR3(2, 2, 2));
}
void Sample::Input()
{

}
