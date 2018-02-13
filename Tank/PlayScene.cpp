/*PlayScene.cpp*/

/*2017-06-16
	狩野 達哉
		プレイシーンのプログラム*/

/****インクルード****/
#include "PlayScene.h"
#include "Tank.h"
/********************/


//コンストラクタ
PlayScene::PlayScene()
{
	//変数の初期化
	ground = nullptr;
	tank = nullptr;
	wall = nullptr;
	star = nullptr;
	tree = nullptr;
}

//デストラクタ
PlayScene::~PlayScene()
{
}

//初期化処理
void PlayScene::Init()
{
	//ループに使う変数をレジストリに登録して高速化
	register int count = 0;

	//ライト作成
	Light *light = Light::Create();
	AddChild(light);

	//地面作成
	ground = Fbx::Create("Assets//ground.fbx");
	AddChild(ground);

	//壁作成
	wall = Fbx::Create("Assets//wall.fbx");
	AddChild(wall);

	//戦車作成
	tank = Tank::Create();
	AddChild(tank);

	//星作成
	star = Fbx::Create("Assets//star.fbx");
	star->SetPosition(20, 0, 20);
	this->AddChild(star);

	//木作成
	while (count < 20)
	{
		tree = Quad::Create("Assets//tree.png");
		tree->SetPosition(rand() % 101 - 50, 0, rand() % 101 - 50);
		tree->SetScale(2, 4, 1);
		
		//地面との判定
		RayCastData treeData;
		treeData.start = tree->GetPosition();
		treeData.start.y += 10;
		treeData.dir = D3DXVECTOR3(0, -1, 0);
		ground->RayCast(&treeData);

		//当たった位置に木を設定
		if (treeData.hit)
		{
			tree->SetPosition(tree->GetPosition().x, tree->GetPosition().y - (treeData.dist - 10), tree->GetPosition().z);
		}

		tree->SetCamera(_pCamera);
		tree->SetIsSort(true);
		AddChild(tree);
		count++;
	}
}

void PlayScene::Update()
{
	//シーンのUpdateを直接呼び出す
	Scene::Update();

	//カメラのターゲットを戦車からに設定
	_pCamera->SetTarget(tank->GetPosition() + D3DXVECTOR3(0, 3, 0));
	D3DXVECTOR3 cameraVector = D3DXVECTOR3(0, 5, -8);
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(tank->GetRotate().y));
	D3DXVec3TransformCoord(&cameraVector, &cameraVector, &mat);
	_pCamera->SetPosition(tank->GetPosition() + cameraVector);

	//カメラをその都度更新
	_pCamera->Update();

	//地面との判定
	//発射位置を少し上にすることで地面の下がりや上がりも対応
	RayCastData data;
	data.start = tank->GetPosition();
	data.start.y += 10;
	data.dir = D3DXVECTOR3(0, -1, 0);
	ground->RayCast(&data);

	//当たった位置に戦車を設定
	if (data.hit)
	{
		tank->SetPosition(tank->GetPosition().x, tank->GetPosition().y - (data.dist - 10), tank->GetPosition().z);
	}


	//壁との判定(前)
	//発射位置を前にして当たったら処理を変化させて
	//壁を貫通させないようにする
	RayCastData data2;
	data2.start = tank->GetPosition();
	data2.dir = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIX mat2;
	D3DXMatrixRotationY(&mat2, D3DXToRadian(tank->GetRotate().y));
	D3DXVec3TransformCoord(&data2.dir, &data2.dir, &mat2);
	wall->RayCast(&data2);
	if (data2.hit && data2.dist < 3.0f)
	{
		tank->SetHit(true, 0);

		//壁刷り
		tank->SetHitNormal(data2.normal);
	}
	else
	{
		tank->SetHit(false, 0);
	}

	//壁との判定(後)
	RayCastData data2Back;
	data2Back.start = tank->GetPosition();
	data2Back.dir = D3DXVECTOR3(0, 0, -1);
	D3DXMATRIX mat2Back;
	D3DXMatrixRotationY(&mat2Back, D3DXToRadian(tank->GetRotate().y));
	D3DXVec3TransformCoord(&data2Back.dir, &data2Back.dir, &mat2Back);
	wall->RayCast(&data2Back);
	if (data2Back.hit && data2Back.dist < 3.0f)
	{
		tank->SetHit(true, 1);

		//壁刷り
		tank->SetHitNormal(data2Back.normal);
	}
	else
	{
		tank->SetHit(false, 1);
	}

	//星の位置を取得して
	//距離の長さが3.50f以内だったらGET
	D3DXVECTOR3 v = tank->GetPosition() - star->GetPosition();

	//ベクトルの距離を取得
	float l = D3DXVec3Length(&v);
	if (l < 3.5f)
	{
		g.ReplaceScene(new ClearScene);
	}
}
