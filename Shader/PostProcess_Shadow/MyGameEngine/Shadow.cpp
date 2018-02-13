#include "Shadow.h"


Shadow::Shadow()
{
}


Shadow::~Shadow()
{
}



// HACK: Node�p���ł͂Ȃ�Fbx�p���ɂȂ��Ă���
// TODO: Node�p���ōs���ׂ�
void Shadow::DrawShadowMap(LPDIRECT3DTEXTURE9 renderTexture)
{
	//���_�o�b�t�@���Z�b�g
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

	//���̏��Ȃ̂�
	//�ʒu�Ɩ@����UV���W
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEX2);

	// �V�F�[�_�[��ݒ�
	_shaderShadowMap->SetMatrix("matWorld", &World());


	_shaderShadowMap->SetMatrix("matView", &ShadowLightView());


	_shaderShadowMap->SetMatrix("matProj", &Projection());


	// �V���h�E�}�b�v
	_shader->SetMatrix("matUV", &ShadowUV());
	_shader->SetMatrix("matLightView", &ShadowLightView());
	_shader->SetTexture("texShadowMap", renderTexture);




	// �V�F�[�_�[��K�p(�����_�����O�J�n)
	_shaderShadowMap->Begin(NULL, 0);

	//�}�e���A���������[�v
	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_materialData[initialize].indexBuffer);
		g.pDevice->SetMaterial(&_materialData[initialize].material);

		// ���[�v���ɓ���邱�Ƃ�
		// 1�̕`��ɐ������K�p�����(�����邱�Ƃ��ł���)
		_shaderShadowMap->BeginPass(0);

		//�`��
		//���_��
		//�}�e���A�����Ƃ̃|���S����
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, _materialData[initialize].polygonCountOfMaterial);

		_shaderShadowMap->EndPass();

		initialize++;
	}
	initialize = 0;

	// �J�n������K���I��������
	_shaderShadowMap->End();
}

D3DXMATRIX Shadow::ShadowLightView()
{
	// ���C�g�r���[�s��
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