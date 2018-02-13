#include "Sample.h"

Sample::Sample()
{
}


Sample::~Sample()
{

	SAFE_RELEASE(_shader);
}

void Sample::Init()
{
	// フライウェイトパターン
	// 1個だけロードして呼び出す
	// Managerクラスなど

	// エラー用変数
	LPD3DXBUFFER error = 0;

	// エフェクトを設定
	// 最後の引数にエラー用変数を入れることで
	// どこでエラーになったかが分かる
	if (FAILED(D3DXCreateEffectFromFile(g.pDevice, "CommonShader.hlsl", NULL, NULL, NULL, NULL, &_shader, &error)))
	{
		//	エラー内容
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}

	if (FAILED(D3DXCreateEffectFromFile(g.pDevice, "WaterShader.hlsl", NULL, NULL, NULL, NULL, &_waterShader, &error)))
	{
		//	エラー内容
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}

	Light *light = Light::Create();
	this->AddChild(light);

	Fbx *water = Fbx::Create("Assets//Water.fbx");
	AddChild(water);
	water->SetShafer(_shader);

	_torus = Fbx::Create("Assets//torus.fbx");
	_torus->SetPosition(-4, 0, 2);
	AddChild(_torus);
	_torus->SetShafer(_shader);

	_torusRed = Fbx::Create("Assets//torusRed.fbx");
	_torusRed->SetPosition(-2, -1, -1);
	this->AddChild(_torusRed);
	_torusRed->SetShafer(_shader);

	_torusPhong = Fbx::Create("Assets//torusPhong.fbx");
	_torusPhong->SetPosition(0, 0, 2);
	this->AddChild(_torusPhong);
	_torusPhong->SetShafer(_shader);

	_torusNormal = Fbx::Create("Assets//torusNormal.fbx");
	_torusNormal->SetPosition(2, -1, -1);
	this->AddChild(_torusNormal);
	_torusNormal->SetShafer(_shader);

	_torusHalf = Fbx::Create("Assets//torusHalf.fbx");
	_torusHalf->SetPosition(4, 0, 2);
	this->AddChild(_torusHalf);
	_torusHalf->SetShafer(_shader);
}


void Sample::Update()
{
	static float rotateY = 0.0f;
	_torus->SetRotate(0, rotateY, 0);
	_torusRed->SetRotate(0, rotateY, 0);
	_torusPhong->SetRotate(0, rotateY, 0);
	_torusNormal->SetRotate(0, rotateY, 0);
	_torusHalf->SetRotate(0, rotateY, 0);
	rotateY += 2;
}

