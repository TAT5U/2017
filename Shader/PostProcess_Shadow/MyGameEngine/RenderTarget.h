
//インクルードガード
#pragma once

/****インクルード****/
#include"Node.h"
/********************/

#include "../resource.h"


class RenderTarget : public Node
{
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};

	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 _indexBuffer;
	LPDIRECT3DTEXTURE9 _renderTexture;

	// 仲介
	LPDIRECT3DSURFACE9 _renderSurface;

	LPDIRECT3DSURFACE9 _renderZBuffer;

	LPDIRECT3DSURFACE9 _defaultSurface;

	LPDIRECT3DSURFACE9 _defaultZBuffer;


	LPD3DXEFFECT _shader;

public:

	//コンストラクタ
	RenderTarget();

	//デストラクタ
	~RenderTarget();

	void Load();
	void Draw();

	void ChangeTarget();
	void ReturnTarget();


	LPDIRECT3DTEXTURE9 GetRenderTexture();
};

