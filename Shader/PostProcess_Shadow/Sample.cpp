#include "Sample.h"






#include "resource.h"
#include "MyGameEngine\RenderTarget.h"


Sample::Sample()
{
	_cubeTexture = nullptr;
	_toonTexture = nullptr;

	_renderTarget = nullptr;
}


Sample::~Sample()
{
	SAFE_RELEASE(_shader);
	SAFE_RELEASE(_waterShader);
	SAFE_RELEASE(_toonShader);
	SAFE_RELEASE(_toonTexture);
	SAFE_RELEASE(_cubeTexture);
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
	if (FAILED(D3DXCreateEffectFromResource(g.pDevice, NULL, MAKEINTRESOURCE(IDR_COMMON_SHADER), NULL, NULL, NULL, NULL, &_shader, &error)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}
	if (FAILED(D3DXCreateEffectFromResource(g.pDevice, NULL, MAKEINTRESOURCE(IDR_WATER_SHADER), NULL, NULL, NULL, NULL, &_waterShader, &error)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}
	if (FAILED(D3DXCreateEffectFromResource(g.pDevice, NULL, MAKEINTRESOURCE(IDR_ENVIROMENT_MAPPING), NULL, NULL, NULL, NULL, &_envShader, &error)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}

	if (FAILED(D3DXCreateEffectFromResource(g.pDevice, NULL, MAKEINTRESOURCE(IDR_TOON_SHADER), NULL, NULL, NULL, NULL, &_toonShader, &error)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}


	if (FAILED(D3DXCreateCubeTextureFromFile(g.pDevice, "Assets/cubeMap.dds", &_cubeTexture)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFile(g.pDevice, "Assets/Toon.png", &_toonTexture)))
	{
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}


	_envShader->SetTexture("texCube", _cubeTexture);

	_toonShader->SetTexture("texToon", _toonTexture);


	Light *light = Light::Create();
	this->AddChild(light);


	_torus = Fbx::Create("Assets//torus.fbx");
	_torus->SetPosition(-4, 0, 2);
	AddChild(_torus);
	_torus->SetShader(_envShader);

	_torusRed = Fbx::Create("Assets//torusRed.fbx");
	_torusRed->SetPosition(-2, -1, -1);
	this->AddChild(_torusRed);
	_torusRed->SetShader(_envShader);

	_torusPhong = Fbx::Create("Assets//torusPhong.fbx");
	_torusPhong->SetPosition(0, 0, 2);
	this->AddChild(_torusPhong);
	_torusPhong->SetShader(_envShader);

	_torusNormal = Fbx::Create("Assets//torusNormal.fbx");
	_torusNormal->SetPosition(2, -1, -1);
	this->AddChild(_torusNormal);
	_torusNormal->SetShader(_envShader);

	_torusHalf = Fbx::Create("Assets//torusHalf.fbx");
	_torusHalf->SetPosition(4, 0, 2);
	this->AddChild(_torusHalf);
	_torusHalf->SetShader(_envShader);

	_water = Water::Create();
	AddChild(_water);
	_water->SetShader(_waterShader);
	_water->SetShaderPass(0);

	_zunko = Zunko::Create();
	_zunko->SetPosition(_zunko->GetPosition().x, _zunko->GetPosition().y, -2);
	AddChild(_zunko);
	_zunko->SetShader(_toonShader);
	_zunko->SetShaderPass(0);


	// 2018-01-23
	// Init関数で生成する
	// コンストラクタで生成すると、他のFbxなどが生成される前にできてしまい表示されない(画像に)
	_renderTarget = new RenderTarget;
	_renderTarget->Load();

	//_star = Star::Create();
	//AddChild(_star);
}


void Sample::Update()
{
	Scene::Update();

	static float rotateY = 0.0f;
	_torus->SetRotate(0, rotateY, 0);
	_torusRed->SetRotate(0, rotateY, 0);
	_torusPhong->SetRotate(0, rotateY, 0);
	_torusNormal->SetRotate(0, rotateY, 0);
	_torusHalf->SetRotate(0, rotateY, 0);
	rotateY += 2;
}


void Sample::Draw()
{
	_renderTarget->ChangeTarget();

	register int i = 2;
	while (i < _pNodes.size())
	{
		{
			((Shadow*)_pNodes[i])->DrawShadowMap(_renderTarget->GetRenderTexture());
		}
		i++;
	}

	//初期化
	i = 0;

	_renderTarget->ReturnTarget();
	Scene::Draw();
}

