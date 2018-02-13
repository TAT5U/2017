#pragma once
#include "Node.h"

class Light : public Node
{
	~Light();
public:
	static Light* Create();
};