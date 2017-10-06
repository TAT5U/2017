/*MiniMapOperation.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "WinScaleSize.h"

// Namespace
USING_NS_CC;

class MiniMapOperation : public TMXTiledMap
{
	// Mini map
	TMXTiledMap *miniMap;
    
    // Background
	Sprite *backGround;
    
    // Mini map position
	Point miniMapPosition;

public:

    // Constructor
	MiniMapOperation();
    
    // Destructor
	~MiniMapOperation();
    
    // Initialization processing
    virtual bool init() override;
    
    // Get mini map position
	Point GetMiniMapPos();

	CREATE_FUNC(MiniMapOperation);
};

