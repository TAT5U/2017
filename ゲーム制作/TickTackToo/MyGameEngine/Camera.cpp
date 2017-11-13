/*Camera.cpp*/

/*2017-09-13
	狩野 達哉
		3DCGを表示する時に使用するCameraプログラム*/

/****インクルード****/
#include "Camera.h"
/********************/


//コンストラクタ
Camera::Camera()
{
	//変数の初期化
	_position = D3DXVECTOR3(0, 0, -10);
	_target = D3DXVECTOR3(0, 0, 0);
	_up = D3DXVECTOR3(0, 1, 0);
	_angle = 60;
	_aspect = (float)g.WINDOW_WIDTH / (float)g.WINDOW_HEIGHT;
	_nearClip = 0.30f;
	_farClip = 1000.0f;

	//単位行列
	//初期化する時などに使用する
	D3DXMatrixIdentity(&_view);
	D3DXMatrixIdentity(&_proj);
}

//デストラクタ
Camera::~Camera()
{
}

//静的関数	カメラの作成
Camera *Camera::Create()
{
	Camera *pCamera = new Camera();
	return pCamera;
}

//更新処理
void Camera::Update()
{
	//ビュー行列作成
	D3DXMatrixLookAtLH(&_view, &_position, &_target, &_up);

	//ビュー行列設定
	g.pDevice->SetTransform(D3DTS_VIEW, &_view);

	//プロジェクション行列作成
	D3DXMatrixPerspectiveFovLH(&_proj, D3DXToRadian(_angle), _aspect, _nearClip, _farClip);

	//プロジェクション行列設定
	g.pDevice->SetTransform(D3DTS_PROJECTION, &_proj);
}