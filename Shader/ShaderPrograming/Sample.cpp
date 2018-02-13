#include "Sample.h"


Sample::Sample()
{
	tours = nullptr;
}


Sample::~Sample()
{
}

void Sample::Init()
{
	//ライト作成
	Light *light = Light::Create();
	AddChild(light);

	tours = Fbx::Create("Assets//Torus.fbx");
	AddChild(tours);
}
void Sample::Update()
{
	tours->SetRotate(tours->GetRotate() + D3DXVECTOR3(2, 2, 2));
}
void Sample::Input()
{

}
