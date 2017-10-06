/*MiniCharacter.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "WinScaleSize.h"
#include "MiniMapOperation.h"

// Namespace
USING_NS_CC;

// Direction identifier
enum  class MiniCharaDirection
{
	Top = 1,
	Right = 2,
	Left = 3
};

class MiniCharacter : public Sprite
{
	// Character position
	Sprite *characterPos;

public:
    
    // Constructor
	MiniCharacter();
    
    // Destructor
	~MiniCharacter();

	// Initialization processing
	virtual bool init() override;

	// Create mini character
	void MiniCharacterCreate(MiniMapOperation *minimap);

	// Mini character move
	void MoveMiniCharacter(int miniTag);
    
    // Mini map position restore
	void RestorePos(int tag);

	CREATE_FUNC(MiniCharacter);
};

