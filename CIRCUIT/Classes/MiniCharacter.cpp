/*MiniCharacter.cpp*/

/*2017-00-22
	Tatsuya Kano
        Create MiniCharacter*/

// Include
#include "MiniCharacter.h"

// Constructor
MiniCharacter::MiniCharacter()
{
    // Initialization
    characterPos = nullptr;
}


// Destructor
MiniCharacter::~MiniCharacter()
{
    
}

// Initialization processing
bool MiniCharacter::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}


// Create mini character
void MiniCharacter::MiniCharacterCreate(MiniMapOperation *minimap)
{
	// Get standard position
	Point standardPosition = minimap->GetMiniMapPos();
    
    // Get scale size
	WinScaleSize winScaleSize;
	Size scaleSize = winScaleSize.SetWinScaleSize();

	// Mini character
	characterPos = Sprite::create("GameScene/images/character.png");
	characterPos->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	characterPos->setScale(scaleSize.width * 0.02, scaleSize.height * 0.02);
    characterPos->setPosition(standardPosition.x + (characterPos->getContentSize().width * characterPos->getScaleX()) / 2, standardPosition.y);
	addChild(characterPos);
    
    // Set tag mini character
	characterPos->setTag(static_cast<int>(MiniCharaDirection::Top));
}

// Mini character move
void MiniCharacter::MoveMiniCharacter(int miniTag)
{
	Vec2 pos;
    
    // Get mini character position now
	pos = characterPos->getPosition();
    
	if (miniTag == static_cast<int>(MiniCharaDirection::Left))
	{
		characterPos->setPositionX(pos.x -= 2 * 0.02);
	}
	if (miniTag == static_cast<int>(MiniCharaDirection::Right))
	{
		characterPos->setPositionX(pos.x += 2 * 0.02);
	}
	if (miniTag == static_cast<int>(MiniCharaDirection::Top) || miniTag < 0)
	{
		characterPos->setPositionY(pos.y += 2 * 0.02);
	}
}

// Mini map position restore
void MiniCharacter::RestorePos(int tag)
{
	if (tag == static_cast<int>(MiniCharaDirection::Left))
	{
		characterPos->setPositionX(characterPos->getPositionX() + 150 * 0.02);
	}
	if (tag == static_cast<int>(MiniCharaDirection::Right))
	{
		characterPos->setPositionX(characterPos->getPositionX() - 150 * 0.02);
	}
	if (tag == static_cast<int>(MiniCharaDirection::Top) || tag < 0)
	{
		characterPos->setPositionY(characterPos->getPositionY() - 150 * 0.02);
	}
}
