/*GameScene.cpp*/

/*2017-07-26
	Tatsuya Kano
		GameScene*/

// Include
#include "GameScene.h"
#include "ResultScene.h"

// Constructor
GameScene::GameScene()
	: touchPos_{ 0.0f, 0.0f }
{
	// Initialization
	map_ = nullptr;
	miniMap_ = nullptr;
	character_ = nullptr;
	miniCharacter_ = nullptr;
	characterLife_ = nullptr;
	_isGameOver = false;
}


// Destructor
GameScene::~GameScene()
{

}


// Initialization processing
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
    
	// FadeIn
	FadePrePare();

	// Map
    {
        map_ = MapOperation::create();
        
        // Assert
        CC_ASSERT(map_);
        addChild(map_);
        
        // Zoom out
        map_->setPositionZ(-300);
    }
    
    
	// MiniMap
    {
        miniMap_ = MiniMapOperation::create();
        
        // Assert
        CC_ASSERT(miniMap_);
        addChild(miniMap_);
    }
    
    
	// Character
    {
        character_ = Character::create();
        
        // Assert
        CC_ASSERT(character_);
        addChild(character_);
        
		// Zoom out
        character_->setPositionZ(-300);
    }
    
    
	// MiniCharacter
    {
        miniCharacter_ = MiniCharacter::create();
        miniCharacter_->MiniCharacterCreate(miniMap_);
        
        // Assert
        CC_ASSERT(miniCharacter_);
        addChild(miniCharacter_);
    }
    
    
	// CharacterLife
    {
        characterLife_ = CharacterLife::create();
        
        // Assert
        CC_ASSERT(characterLife_);
        addChild(characterLife_);
    }
	input();
	scheduleUpdate();
	return true;
}


// Input processing
void GameScene::input()
{
	// Touch event listner
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	
	// Touching
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		// Get touching position
		touchPos_ = touch->getLocation();

		return true;
	};

	// Touch moved
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		if (_isGameOver == false)
		{
			// Get direction
			Vec2 slanting = touch->getLocation() - touchPos_;

			//Tag change with direction
			if ((slanting.x < 0) && (slanting.x < slanting.y))
			{
				// Set tag
				map_->setTag(static_cast<int>(MoveDirection::Left));
			}
			else if ((slanting.x > 0) && (slanting.x > slanting.y))
			{
				// Set tag
				map_->setTag(static_cast<int>(MoveDirection::Right));
			}
			else if ((slanting.y > 0) && (slanting.x < slanting.y))
			{
				// Set tag
				map_->setTag(static_cast<int>(MoveDirection::Top));
			}
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


// Update processing
void GameScene::update(float dt)
{
	// FadeIn
	if (_isFadeIn)
	{
		FadeIn(100.0f);
	}
	else
	{
		if (_isGameOver == false)
		{
			// Count
			int i = 0;

			while (i < 360)
			{
				// Get layer name
				int layerNum = map_->GetLayerName(character_->GetPos(i));

				// Out
				if (layerNum == 4)
				{
					// Game over
					if (characterLife_->DecreaseCharacterLife() == true)
					{
						// Stop
						map_->unscheduleUpdate();
						character_->unscheduleUpdate();
						characterLife_->unscheduleUpdate();
						//this->unscheduleUpdate();

						////////////////////////Hatakeyama Add//////////////////////////////////////////////////////
						//exit(1);
						//Director::getInstance()->replaceScene(ResultScene::create());
						_isGameOver = true;
					}
					else
					{
						// Decreased life and mini character position restore
						miniCharacter_->RestorePos(map_->getTag());
						map_->RestorePos(map_->getTag());
					}
				}
				i++;
			}

			//Map & miniCharacter move
			map_->MoveMap(map_->getTag());
			miniCharacter_->MoveMiniCharacter(map_->getTag());
		}
		else
		{
			FadeOut(100.0f, ResultScene::create());
		}

	}
}
