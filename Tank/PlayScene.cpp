/*PlayScene.cpp*/

/*2017-06-16
	��� �B��
		�v���C�V�[���̃v���O����*/

/****�C���N���[�h****/
#include "PlayScene.h"
#include "Tank.h"
/********************/


//�R���X�g���N�^
PlayScene::PlayScene()
{
	//�ϐ��̏�����
	ground = nullptr;
	tank = nullptr;
	wall = nullptr;
	star = nullptr;
	tree = nullptr;
}

//�f�X�g���N�^
PlayScene::~PlayScene()
{
}

//����������
void PlayScene::Init()
{
	//���[�v�Ɏg���ϐ������W�X�g���ɓo�^���č�����
	register int count = 0;

	//���C�g�쐬
	Light *light = Light::Create();
	AddChild(light);

	//�n�ʍ쐬
	ground = Fbx::Create("Assets//ground.fbx");
	AddChild(ground);

	//�Ǎ쐬
	wall = Fbx::Create("Assets//wall.fbx");
	AddChild(wall);

	//��ԍ쐬
	tank = Tank::Create();
	AddChild(tank);

	//���쐬
	star = Fbx::Create("Assets//star.fbx");
	star->SetPosition(20, 0, 20);
	this->AddChild(star);

	//�؍쐬
	while (count < 20)
	{
		tree = Quad::Create("Assets//tree.png");
		tree->SetPosition(rand() % 101 - 50, 0, rand() % 101 - 50);
		tree->SetScale(2, 4, 1);
		
		//�n�ʂƂ̔���
		RayCastData treeData;
		treeData.start = tree->GetPosition();
		treeData.start.y += 10;
		treeData.dir = D3DXVECTOR3(0, -1, 0);
		ground->RayCast(&treeData);

		//���������ʒu�ɖ؂�ݒ�
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
	//�V�[����Update�𒼐ڌĂяo��
	Scene::Update();

	//�J�����̃^�[�Q�b�g���Ԃ���ɐݒ�
	_pCamera->SetTarget(tank->GetPosition() + D3DXVECTOR3(0, 3, 0));
	D3DXVECTOR3 cameraVector = D3DXVECTOR3(0, 5, -8);
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(tank->GetRotate().y));
	D3DXVec3TransformCoord(&cameraVector, &cameraVector, &mat);
	_pCamera->SetPosition(tank->GetPosition() + cameraVector);

	//�J���������̓s�x�X�V
	_pCamera->Update();

	//�n�ʂƂ̔���
	//���ˈʒu��������ɂ��邱�ƂŒn�ʂ̉������オ����Ή�
	RayCastData data;
	data.start = tank->GetPosition();
	data.start.y += 10;
	data.dir = D3DXVECTOR3(0, -1, 0);
	ground->RayCast(&data);

	//���������ʒu�ɐ�Ԃ�ݒ�
	if (data.hit)
	{
		tank->SetPosition(tank->GetPosition().x, tank->GetPosition().y - (data.dist - 10), tank->GetPosition().z);
	}


	//�ǂƂ̔���(�O)
	//���ˈʒu��O�ɂ��ē��������珈����ω�������
	//�ǂ��ђʂ����Ȃ��悤�ɂ���
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

		//�Ǎ���
		tank->SetHitNormal(data2.normal);
	}
	else
	{
		tank->SetHit(false, 0);
	}

	//�ǂƂ̔���(��)
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

		//�Ǎ���
		tank->SetHitNormal(data2Back.normal);
	}
	else
	{
		tank->SetHit(false, 1);
	}

	//���̈ʒu���擾����
	//�����̒�����3.50f�ȓ���������GET
	D3DXVECTOR3 v = tank->GetPosition() - star->GetPosition();

	//�x�N�g���̋������擾
	float l = D3DXVec3Length(&v);
	if (l < 3.5f)
	{
		g.ReplaceScene(new ClearScene);
	}
}
