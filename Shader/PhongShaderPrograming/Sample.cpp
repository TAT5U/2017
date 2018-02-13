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
	//ライト作成
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
