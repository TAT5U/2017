#pragma once
#include <d3dx9.h>

class MyRect
{
public:
	float _left;
	float _top;
	float _width;
	float _height;

	MyRect();
	MyRect(float left, float top, float width, float height);
	~MyRect();

	BOOL IntersectsRect(MyRect targetRect);
	BOOL MyRect::ContainsPoint(D3DXVECTOR3 targetPos);
};