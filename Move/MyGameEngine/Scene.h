#pragma once

#include "Global.h"
#include "Sprite.h"
#include "Label.h"
#include "Quad.h"
#include "Light.h"
#include <vector>

class Camera;
class Scene
{
	
protected:
	std::vector<Node*> _nodes;
	Camera*	_camera;
public:
	Scene();
	virtual ~Scene();
	void AddChild(Node* pNode);
	virtual void Draw();
	virtual void Init()   = 0;
	virtual void Update();
	virtual void Input();

	void RemoveChild(Node* pNode);

	class NodeSort
	{
	public:
		bool operator()(Node* a, Node*b)
		{
			if (a->GetDistance() > b->GetDistance())
			{
				return true;
			}
			return false;
		}
	};
};