/*Sprite.cpp*/

/*2017-06-11
	狩野 達哉
		画像を表示するために
			使用するSpriteプログラム*/

/****インクルード****/
#include "Sprite.h"
#include "Fade.h"
/********************/


//コンストラクタ
Sprite::Sprite()
{
	//変数の初期化
	_pSprite = nullptr;
	_pTexture = nullptr;
	_cut = MyRect(0, 0, 0, 0);
	//alpha = 0.0f;
}

//デストラクタ
Sprite::~Sprite()
{
	//解放処理
	SAFE_RELEASE(_pTexture);
	SAFE_RELEASE(_pSprite);
}

//静的関数	Spriteオブジェクトを作成してLoad関数を呼び、アドレスを返す
Sprite *Sprite::Create(LPCSTR fileName, MyRect cut)
{
	Sprite *pSprite = new Sprite();
	pSprite->Load(fileName, cut);
	return pSprite;
}

//読み込み処理
void Sprite::Load(LPCSTR fileName, MyRect cut)
{
	//スプライトオブジェクトを作成
	D3DXCreateSprite(g.pDevice, &_pSprite);

	//テクスチャオブジェクトの作成
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);

	//全体表示
	if (cut._left == -999)
	{
		//テクスチャのサイズを取得
		//D3DSURFACE_DESC d3dds;
		//_pTexture->GetLevelDesc(0, &d3dds);
		//_size.x = d3dds.Width;
		//_size.y = d3dds.Height;

		/********************2017-10-12********************/
		//修正
		//テクスチャのサイズを2の累乗で作成ではなく
		//スプライトのサイズに沿って作成されるように変更
		//スプライトの情報
		D3DXIMAGE_INFO textureInfo;

		//情報を格納
		D3DXGetImageInfoFromFile(fileName, &textureInfo);

		//サイズ設定
		_size.x = textureInfo.Width;
		_size.y = textureInfo.Height;
		/**************************************************/

		//切抜き範囲
		_cut = MyRect(0, 0, _size.x, _size.y);
	}

	//範囲指定表示
	else
	{
		//切抜き範囲
		_cut = cut;

		//幅と高さを切り抜いたサイズに変更
		_size.x = _cut._width;
		_size.y = _cut._height;
	}
}

//描画処理
void Sprite::Draw()
{
	//移動行列
	D3DXMATRIX trans;

	//移動行列格納
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//回転行列
	D3DXMATRIX rotate;

	//回転行列格納
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(_rotate.z));

	//拡大縮小行列
	D3DXMATRIX scale;

	//拡大縮小行列格納
	D3DXMatrixScaling(&scale, _scale.x,_scale.y,_scale.z);

	//移動・回転・拡大縮小を行わせるための行列
	//拡大縮小 * 回転 * 移動	順番を変えると変わる
	//ワールド行列
	D3DXMATRIX world = scale * rotate * trans;

	//行列をセット
	_pSprite->SetTransform(&world);

	//cocos2dxでは0が下だったがDirectXでは0が上になっている
	//アンカーポイント設定	画像の中心に設定
	anchor = D3DXVECTOR3(_size.x*_anchorPoint.x, _size.y*_anchorPoint.y, 0);

	//切抜き範囲
	//左・上・右(左 + 幅)・下(上 + 高さ)
	//メンバ変数でRECTを宣言した場合
	//縮小変換が必要とされエラーが生じる(VS2015で)
	RECT cut = { _cut._left,_cut._top,_cut._left + _cut._width,_cut._top + _cut._height };

	_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (!g.GetAlphaFlg())
	{
		//スプライトにテクスチャを貼り付けて描画	不透明度・赤・緑・青
		_pSprite->Draw(_pTexture, &cut, &anchor, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		//スプライトにテクスチャを貼り付けて描画	不透明度・赤・緑・青
		_pSprite->Draw(_pTexture, &cut, &anchor, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
	_pSprite->End();
}

//切抜き範囲をセット
void Sprite::SetRect(MyRect cut)
{
	//切抜き範囲
	_cut = cut;

	//範囲を変更したら必ずサイズも変更する
	//幅と高さを切り抜いたサイズに変更
	_size.x = _cut._width;
	_size.y = _cut._height;
}

void Sprite::SetNoFade()
{
	g.pFade->NoFade(this);
}