/*Sprite.cpp*/

/*2017-06-11
	��� �B��
		�摜��\�����邽�߂�
			�g�p����Sprite�v���O����*/

/****�C���N���[�h****/
#include "Sprite.h"
#include "Fade.h"
/********************/


//�R���X�g���N�^
Sprite::Sprite()
{
	//�ϐ��̏�����
	_pSprite = nullptr;
	_pTexture = nullptr;
	_cut = MyRect(0, 0, 0, 0);
	//alpha = 0.0f;
}

//�f�X�g���N�^
Sprite::~Sprite()
{
	//�������
	SAFE_RELEASE(_pTexture);
	SAFE_RELEASE(_pSprite);
}

//�ÓI�֐�	Sprite�I�u�W�F�N�g���쐬����Load�֐����ĂсA�A�h���X��Ԃ�
Sprite *Sprite::Create(LPCSTR fileName, MyRect cut)
{
	Sprite *pSprite = new Sprite();
	pSprite->Load(fileName, cut);
	return pSprite;
}

//�ǂݍ��ݏ���
void Sprite::Load(LPCSTR fileName, MyRect cut)
{
	//�X�v���C�g�I�u�W�F�N�g���쐬
	D3DXCreateSprite(g.pDevice, &_pSprite);

	//�e�N�X�`���I�u�W�F�N�g�̍쐬
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);

	//�S�̕\��
	if (cut._left == -999)
	{
		//�e�N�X�`���̃T�C�Y���擾
		//D3DSURFACE_DESC d3dds;
		//_pTexture->GetLevelDesc(0, &d3dds);
		//_size.x = d3dds.Width;
		//_size.y = d3dds.Height;

		/********************2017-10-12********************/
		//�C��
		//�e�N�X�`���̃T�C�Y��2�̗ݏ�ō쐬�ł͂Ȃ�
		//�X�v���C�g�̃T�C�Y�ɉ����č쐬�����悤�ɕύX
		//�X�v���C�g�̏��
		D3DXIMAGE_INFO textureInfo;

		//�����i�[
		D3DXGetImageInfoFromFile(fileName, &textureInfo);

		//�T�C�Y�ݒ�
		_size.x = textureInfo.Width;
		_size.y = textureInfo.Height;
		/**************************************************/

		//�ؔ����͈�
		_cut = MyRect(0, 0, _size.x, _size.y);
	}

	//�͈͎w��\��
	else
	{
		//�ؔ����͈�
		_cut = cut;

		//���ƍ�����؂蔲�����T�C�Y�ɕύX
		_size.x = _cut._width;
		_size.y = _cut._height;
	}
}

//�`�揈��
void Sprite::Draw()
{
	//�ړ��s��
	D3DXMATRIX trans;

	//�ړ��s��i�[
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//��]�s��
	D3DXMATRIX rotate;

	//��]�s��i�[
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(_rotate.z));

	//�g��k���s��
	D3DXMATRIX scale;

	//�g��k���s��i�[
	D3DXMatrixScaling(&scale, _scale.x,_scale.y,_scale.z);

	//�ړ��E��]�E�g��k�����s�킹�邽�߂̍s��
	//�g��k�� * ��] * �ړ�	���Ԃ�ς���ƕς��
	//���[���h�s��
	D3DXMATRIX world = scale * rotate * trans;

	//�s����Z�b�g
	_pSprite->SetTransform(&world);

	//cocos2dx�ł�0������������DirectX�ł�0����ɂȂ��Ă���
	//�A���J�[�|�C���g�ݒ�	�摜�̒��S�ɐݒ�
	anchor = D3DXVECTOR3(_size.x*_anchorPoint.x, _size.y*_anchorPoint.y, 0);

	//�ؔ����͈�
	//���E��E�E(�� + ��)�E��(�� + ����)
	//�����o�ϐ���RECT��錾�����ꍇ
	//�k���ϊ����K�v�Ƃ���G���[��������(VS2015��)
	RECT cut = { _cut._left,_cut._top,_cut._left + _cut._width,_cut._top + _cut._height };

	_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (!g.GetAlphaFlg())
	{
		//�X�v���C�g�Ƀe�N�X�`����\��t���ĕ`��	�s�����x�E�ԁE�΁E��
		_pSprite->Draw(_pTexture, &cut, &anchor, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		//�X�v���C�g�Ƀe�N�X�`����\��t���ĕ`��	�s�����x�E�ԁE�΁E��
		_pSprite->Draw(_pTexture, &cut, &anchor, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
	_pSprite->End();
}

//�ؔ����͈͂��Z�b�g
void Sprite::SetRect(MyRect cut)
{
	//�ؔ����͈�
	_cut = cut;

	//�͈͂�ύX������K���T�C�Y���ύX����
	//���ƍ�����؂蔲�����T�C�Y�ɕύX
	_size.x = _cut._width;
	_size.y = _cut._height;
}

void Sprite::SetNoFade()
{
	g.pFade->NoFade(this);
}