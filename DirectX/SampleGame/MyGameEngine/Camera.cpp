/*Camera.cpp*/

/*2017-09-13
	狩野 達哉
		3DCGを表示する時に使用するCameraプログラム*/

#include "Camera.h"


Camera::Camera()
{
	// 変数の初期化

	// 単位行列
	// 初期化する時などに使用する
	D3DXMatrixIdentity(&_view);
}


Camera::~Camera()
{
}

Camera *Camera::Create()
{
	Camera *pCamera = new Camera();
	return pCamera;
}

void Camera::Update()
{

}