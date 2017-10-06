/*CharacterLife.cpp*/

/*2016-07-26
    Tatsuya Kano
        Create Character life*/

// Include
#include "CharacterLife.h"

// Initialization character life
void InitNullptr(Sprite **pSprite, int element)
{
	pSprite[element - 1] = nullptr;
	if (element > 1)
	{
		element--;
		InitNullptr(pSprite, element);
	}
}


// Constructor
CharacterLife::CharacterLife()
{
	InitNullptr(characterLife, 3);
    i = 0;
}


// Destructor
CharacterLife::~CharacterLife()
{

}


// Initialization processing
bool CharacterLife::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	// Get scale size
	WinScaleSize winScaleSize;
	Size scaleSize = winScaleSize.SetWinScaleSize();

    // Life space
	int nextLifePos = 5;
    
    // Character life
	while (i<3)
	{
		characterLife[i] = Sprite::create("GameScene/images/LIFE.png");
		characterLife[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
		characterLife[i]->setScale(scaleSize.width, scaleSize.height);
        characterLife[i]->setPosition(Director::getInstance()->getWinSize().width - characterLife[i]->getContentSize().width / 2 - nextLifePos, Director::getInstance()->getWinSize().height);
		addChild(characterLife[i]);
        
        // Get life space and position
		nextLifePos = nextLifePos + characterLife[i]->getContentSize().width + 5;
		i++;
	}
	return true;
}


// Decrease life
bool CharacterLife::DecreaseCharacterLife()
{
    
    // End
	if (i <= 0)
	{
		return true;
	}
    
    // Remove life
	characterLife[i - 1]->removeFromParent();
    
	i--;

	return false;
}
