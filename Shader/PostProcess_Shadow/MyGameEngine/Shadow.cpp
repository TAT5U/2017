#include "Shadow.h"


Shadow::Shadow()
{
}


Shadow::~Shadow()
{
}



// HACK: Node継承ではなくFbx継承になっている
// TODO: Node継承で行うべき
void Shadow::DrawShadowMap(LPDIRECT3DTEXTURE9 renderTexture)
{
	//頂点バッファをセット
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

	//何の情報なのか
	//位置と法線とUV座標
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEX2);

	// シェーダーを設定
	_shaderShadowMap->SetMatrix("matWorld", &World());


	_shaderShadowMap->SetMatrix("matView", &ShadowLightView());


	_shaderShadowMap->SetMatrix("matProj", &Projection());


	// シャドウマップ
	_shader->SetMatrix("matUV", &ShadowUV());
	_shader->SetMatrix("matLightView", &ShadowLightView());
	_shader->SetTexture("texShadowMap", renderTexture);




	// シェーダーを適用(レンダリング開始)
	_shaderShadowMap->Begin(NULL, 0);

	//マテリアル数分ループ
	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_materialData[initialize].indexBuffer);
		g.pDevice->SetMaterial(&_materialData[initialize].material);

		// ループ内に入れることで
		// 1つの描画に正しく適用される(分けることができる)
		_shaderShadowMap->BeginPass(0);

		//描画
		//頂点数
		//マテリアルごとのポリゴン数
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, _materialData[initialize].polygonCountOfMaterial);

		_shaderShadowMap->EndPass();

		initialize++;
	}
	initialize = 0;

	// 開始したら必ず終了させる
	_shaderShadowMap->End();
}

D3DXMATRIX Shadow::ShadowLightView()
{
	// ライトビュー行列
	D3DXMATRIX lightView;
	D3DXMatrixLookAtLH(&lightView, &(D3DXVECTOR3(1, -1, 1) * -8), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));

	return lightView;
}

D3DXMATRIX Shadow::ShadowUV()
{
	D3DXMATRIX matUV;
	ZeroMemory(&matUV, sizeof(D3DXMATRIX));
	matUV._11 = 0.50f;
	matUV._22 = -0.50f;
	matUV._33 = 1.0f;
	matUV._41 = 0.50f;
	matUV._42 = 0.50f;
	matUV._44 = 1.0f;

	return matUV;
}