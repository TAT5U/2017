/*Character.cpp*/

/*2017-07-26
	Tatsuya Kano
        Create Character*/

// Include
#include "Character.h"

// Constructor
Character::Character()
{
    // Initialization
    character = nullptr;
    radius = 0.0f;
}


// Destructor
Character::~Character()
{
    
}


// Initialization processing
bool Character::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// Get display size
	Size displaySize = Director::getInstance()->getVisibleSize();

	// Get scale size
	WinScaleSize winScaleSize;
	Size scaleSize = winScaleSize.SetWinScaleSize();

	// Character
	character = Sprite::create("GameScene/images/character.png");
    character->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	character->setScale(scaleSize.width, scaleSize.height);
	character->setPosition(displaySize / 2);
	addChild(character);
    
    // Get radius
	radius = character->getContentSize().width / 2;
    
	return true;
}


// Get character position
Point Character::GetPos(int i)
{
    return character->getPosition() + Point(cosf(i) * radius, sinf(i) * radius);
}



