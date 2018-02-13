#include "Sprite.h"


Sprite::Sprite()
{
	_pSprite = nullptr;
	_pTexture = nullptr;

}


Sprite::~Sprite()
{
	SAFE_RELEASE(_pTexture);
	SAFE_RELEASE(_pSprite);
}


Sprite* Sprite::Create(LPCSTR fileName, MyRect cut)
{
	Sprite* pSprite = new Sprite();
	pSprite->Load(fileName, cut);
	return pSprite;
}


//読み込み
void Sprite::Load(LPCSTR fileName, MyRect cut)
{
	//スプライトオブジェクト作成
	D3DXCreateSprite(g.pDevice, &_pSprite);

	//テクスチャオブジェクトの作成
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);

	//全体表示
	if (cut._left == -999)
	{
		//テクスチャのサイズを取得
		D3DSURFACE_DESC d3dds;
		_pTexture->GetLevelDesc(0, &d3dds);
		_size.x = d3dds.Width;
		_size.y = d3dds.Height;

		//切抜き範囲
		_cut = MyRect(0, 0, _size.x, _size.y);
	}

	//切抜き範囲指定
	else
	{

		//切抜き範囲
		_cut = cut;
		_size.x = cut._width;
		_size.y = cut._height;
	}
}

//描画
void Sprite::Draw()
{
	//移動行列
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, 0);

	//回転行列
	D3DXMATRIX rotate;
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(_rotate.z));

	//拡大縮小
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, 1);

	//ワールド行列
	D3DXMATRIX world = scale * rotate * trans;

	//変換行列をセット
	_pSprite->SetTransform(&world);

	//アンカーポイント
	D3DXVECTOR3 anchor = D3DXVECTOR3(_size.x * _anchorPoint.x, _size.y * _anchorPoint.y, 0);

	//切抜き範囲
	RECT cut = { _cut._left, _cut._top, _cut._width, _cut._height};

	_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	_pSprite->Draw(_pTexture, &cut, &anchor, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	_pSprite->End();
}


//切り抜き範囲をセット
void Sprite::SetRect(MyRect cut)
{
	_cut = cut;
	_size.x = cut._width;
	_size.y = cut._height;
}
