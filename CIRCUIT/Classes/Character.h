/*Character.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "WinScaleSize.h"

// Namespace
USING_NS_CC;

class Character : public Sprite
{
    // Character
    Sprite *character;
    
    // Radius
    float radius;
    
public:

	// Constructor
	Character();

	// Destructor
	~Character();
    
    // Initialization processing
	virtual bool init() override;
    
    // Get character position
    Point GetPos(int i);
    
	CREATE_FUNC(Character);
};
