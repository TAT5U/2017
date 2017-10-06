/*MapOperation.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "WinScaleSize.h"

// Namespace
USING_NS_CC;

// Direction identifier
enum  class MoveDirection
{
	Top = 1,
	Right = 2,
	Left = 3
};

class MapOperation : public TMXTiledMap
{
    // Map
	TMXTiledMap *map;
    
    // Remove prev position
	Vec2 prevPos;

public:

	// Constructor
	MapOperation();

	// Destructor
	~MapOperation();
    
    // Initialization processing
	virtual bool init() override;
    
    // Map move
	void MoveMap(int tag);

    // Get layer name and "SAFE" or "OUT"
    int GetLayerName(Point pt);
    
    // Map position restore
	void RestorePos(int tag);

	CREATE_FUNC(MapOperation);
};
