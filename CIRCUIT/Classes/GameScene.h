/*GameScene.h*/

#pragma once

// Include
#include "cocos2d.h"
#include "MapOperation.h"
#include "MiniMapOperation.h"
#include "Character.h"
#include "MiniCharacter.h"
#include "CharacterLife.h"
#include "MyScene.h"

class GameScene : public MyScene
{
    // Map
	MapOperation *map_;

	// MiniMap
	MiniMapOperation *miniMap_;
    
    // Character
	Character *character_;

	// MiniCharacter
	MiniCharacter *miniCharacter_;
    
    // Life
	CharacterLife *characterLife_;
    
	// Touching position
	Vec2 touchPos_;

	bool _isGameOver;
    
public:

	// Constructor
	GameScene();

	// Destructor
	~GameScene();
    
    // Initialization processing
	virtual bool init() override;
    
    // Input processing
	void input();
    
    // Update processing
    virtual void update(float dt) override;
    
	CREATE_FUNC(GameScene);
};
