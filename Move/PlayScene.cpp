#include "PlayScene.h"
#include <time.h>
#include <stdlib.h>


PlayScene::PlayScene()
{
	_redBall = nullptr;
	_blueBall = nullptr;
}


PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	srand((unsigned)time(NULL));


	//赤いボール
	_redBall = Sprite::Create("Assets\\RedBall.png");
	_redBall->SetPosition((rand() % 400) + 400, 300 );	//位置はランダム
	this->AddChild(_redBall);

	//青いボール
	_blueBall = Sprite::Create("Assets\\BlueBall.png");
	_blueBall->SetPosition(100, 100);
	this->AddChild(_blueBall);
}

void PlayScene::Update()
{
	//青ボール移動
	//D3DXVECTOR3 pos = _blueBall->GetPosition();
	//D3DXVECTOR3 redBallPos = _redBall->GetPosition();
	//D3DXVec3Normalize(&redBallPos, &D3DXVECTOR3(redBallPos - pos));

	//pos += D3DXVECTOR3(redBallPos);

	//_blueBall->SetPosition(pos);

	time_ += 0.01f;

	// Unityの左右運動
	_blueBall->SetPosition(D3DXVECTOR3(_blueBall->GetPosition().x + sin(time_ * 2) * 5.0f, _blueBall->GetPosition().y, _blueBall->GetPosition().z));


	// Unityの振り子運動
	float x = _redBall->GetPosition().x + cos(time_ * 2) * 4.0;
	float y = _redBall->GetPosition().y + sin(time_ * 2) * 4.0;
	float z = _redBall->GetPosition().z + 0.0f;

	_redBall->SetPosition(D3DXVECTOR3(x, y, z));
//
}

void PlayScene::Input()
{
	//D3DXVECTOR3 redPos = _redBall->GetPosition();

	//if (g.pInput->IsKeyPush(DIK_UP))
	//{
	//	redPos.y -= 3;
	//}
	//else if (g.pInput->IsKeyPush(DIK_DOWN))
	//{
	//	redPos.y += 3;
	//}

	//if (g.pInput->IsKeyPush(DIK_RIGHT))
	//{
	//	redPos.x += 3;
	//}
	//else if (g.pInput->IsKeyPush(DIK_LEFT))
	//{
	//	redPos.x -= 3;
	//}
	//_redBall->SetPosition(redPos);
}

