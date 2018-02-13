#include "MyRect.h"


MyRect::MyRect()
{
	_left = 0.0f;
	_top = 0.0f;
	_width = 0.0f;
	_height = 0.0f;

}


MyRect::MyRect(float left, float top, float width, float height)
{
	_left = left;
	_top = top;
	_width = width;
	_height = height;
}

MyRect::~MyRect()
{
}


BOOL MyRect::IntersectsRect(MyRect targetRect)
{
	if (_left <= targetRect._left + targetRect._width &&
		_left + _width >= targetRect._left &&
		_top <= targetRect._top + targetRect._height &&
		_top + _height >= targetRect._top)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL MyRect::ContainsPoint(D3DXVECTOR3 targetPos)
{
	if (_left + _width >= targetPos.x && _left <= targetPos.x &&
		_top + _height >= targetPos.y && _top <= targetPos.y)
	{
		return TRUE;
	}
	return FALSE;
}