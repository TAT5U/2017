/*CharacterLife.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "WinScaleSize.h"

// Namespace
USING_NS_CC;

class CharacterLife : public Sprite
{
    // Chracter life
	Sprite *characterLife[3];

    // Count
	int i;
    
public:

	// Constructor
	CharacterLife();

	// Destructor
	~CharacterLife();
    
    // Initialization processing
	virtual bool init() override;
    
    // Decrease life
	bool DecreaseCharacterLife();

	CREATE_FUNC(CharacterLife);
};
