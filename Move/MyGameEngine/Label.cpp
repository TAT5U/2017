#include "Label.h"


Label::Label()
{
	_pFont = nullptr;
}


Label::~Label()
{
	SAFE_RELEASE(_pFont);
}

Label* Label::Create(LPCSTR  str, LPCSTR  font, int size)
{
	Label* pLabel = new Label();
	pLabel->Load(font, size);
	return pLabel;
}


void Label::Load(LPCSTR  font, int size)
{
	D3DXCreateFont(g.pDevice, size, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, font, &_pFont);
}

void Label::Draw()
{
	RECT rect;
	rect.left =		_position.x - _size.x * _anchorPoint.x;
	rect.top =		_position.y - _size.y * _anchorPoint.y;
	rect.right =	rect.left + _size.x;
	rect.bottom =	rect.top + _size.y;
	_pFont->DrawText(NULL, _string, -1, &rect, DT_LEFT | DT_TOP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Label::SetString(LPCSTR str)
{
	strcpy_s(_string, str);

	RECT rect = { 0, 0, 0, 0 };
	_pFont->DrawText(NULL, _string, -1, &rect, DT_CALCRECT, NULL);
	_size.x = rect.right;
	_size.y = rect.bottom;
}