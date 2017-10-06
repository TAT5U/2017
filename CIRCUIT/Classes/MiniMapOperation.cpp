/*MiniMapOperation.cpp*/

/*2017-09-22
	Tatsuya Kano
        Create MiniMap*/

// Include
#include "MiniMapOperation.h"

// Constructor
MiniMapOperation::MiniMapOperation()
    : miniMapPosition{0.0f, 0.0f}
{
    // Initialization
    miniMap = nullptr;
    backGround = nullptr;
}


// Destructor
MiniMapOperation::~MiniMapOperation()
{
    
}


// Initialization processing
bool MiniMapOperation::init()
{
	if (!TMXTiledMap::init())
	{
		return false;
	}

	// Get display size
	Size displaySize = Director::getInstance()->getVisibleSize();
    
    // Get scale size
	WinScaleSize winScaleSize;
	Size scaleSize = winScaleSize.SetWinScaleSize();
    
    // Position count x and y mini map version
	int x = 0, y = 0;
    
    // Mini map background
	backGround = Sprite::create("GameScene/images/bk.png");
	backGround->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	backGround->setScale(scaleSize.width * 0.2, scaleSize.height * 0.2);
    
    // Mini map
	miniMap = TMXTiledMap::create("GameScene/images/Stages/STAGE1.tmx");
	miniMap->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	miniMap->setScale(scaleSize.width * 0.02, scaleSize.height * 0.02);
    
    // Get layer name "START" position and set
	TMXLayer *startPos = miniMap->getLayer("START");
    
    // Get layer name "START" position and set
	while (y<10)
	{
		while (x<5)
		{
            // No tile
			if (startPos->getTileAt(Vec2(x, 10 - y - 1)) == nullptr)
			{

			}
			else
			{
				miniMapPosition = startPos->getTileAt(Vec2(x, 10 - y - 1))->getPosition();
				break;
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
    
    // Set mini map and background position
	miniMap->setPosition(displaySize.width / 10, displaySize.height / 10);
	backGround->setPosition(displaySize.width / 10, displaySize.height / 10);

	addChild(backGround);
	addChild(miniMap);

	return true;
}

// Get mini map position
Point MiniMapOperation::GetMiniMapPos()
{
	return miniMap->getPosition() + miniMapPosition * miniMap->getScale();
}
