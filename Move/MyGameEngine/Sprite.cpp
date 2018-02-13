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


//�ǂݍ���
void Sprite::Load(LPCSTR fileName, MyRect cut)
{
	//�X�v���C�g�I�u�W�F�N�g�쐬
	D3DXCreateSprite(g.pDevice, &_pSprite);

	//�e�N�X�`���I�u�W�F�N�g�̍쐬
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);

	//�S�̕\��
	if (cut._left == -999)
	{
		//�e�N�X�`���̃T�C�Y���擾
		D3DSURFACE_DESC d3dds;
		_pTexture->GetLevelDesc(0, &d3dds);
		_size.x = d3dds.Width;
		_size.y = d3dds.Height;

		//�ؔ����͈�
		_cut = MyRect(0, 0, _size.x, _size.y);
	}

	//�ؔ����͈͎w��
	else
	{

		//�ؔ����͈�
		_cut = cut;
		_size.x = cut._width;
		_size.y = cut._height;
	}
}

//�`��
void Sprite::Draw()
{
	//�ړ��s��
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, 0);

	//��]�s��
	D3DXMATRIX rotate;
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(_rotate.z));

	//�g��k��
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, 1);

	//���[���h�s��
	D3DXMATRIX world = scale * rotate * trans;

	//�ϊ��s����Z�b�g
	_pSprite->SetTransform(&world);

	//�A���J�[�|�C���g
	D3DXVECTOR3 anchor = D3DXVECTOR3(_size.x * _anchorPoint.x, _size.y * _anchorPoint.y, 0);

	//�ؔ����͈�
	RECT cut = { _cut._left, _cut._top, _cut._width, _cut._height};

	_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	_pSprite->Draw(_pTexture, &cut, &anchor, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	_pSprite->End();
}


//�؂蔲���͈͂��Z�b�g
void Sprite::SetRect(MyRect cut)
{
	_cut = cut;
	_size.x = cut._width;
	_size.y = cut._height;
}
