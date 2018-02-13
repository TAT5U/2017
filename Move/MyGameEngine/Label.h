#pragma once
#include "Node.h"

class Label: public Node
{
	LPD3DXFONT _pFont;
	TCHAR _string[256];     //•\Ž¦‚·‚é•¶Žš—ñ
public:
	Label();
	~Label();
	static Label* Create(LPCSTR  str, LPCSTR  font, int size);
	void Load(LPCSTR  font, int size);
	void Draw();
	void SetString(LPCSTR str);
};