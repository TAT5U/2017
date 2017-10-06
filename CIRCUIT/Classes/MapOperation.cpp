/*MapOperation.cpp*/

/*2017-07-26
	Tatsuya Kano
        Create Map*/

// Include
#include "MapOperation.h"

// Constructor
MapOperation::MapOperation()
	: prevPos{ 0.0f, 0.0f }
{
    // Initialization
    map = nullptr;
}


// Destructor
MapOperation::~MapOperation()
{

}


// Initialization processing
bool MapOperation::init()
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
    
    // Position count x and y
	int x = 0, y = 0;
    
    // Map
	map = TMXTiledMap::create("GameScene/images/Stages/STAGE1.tmx");
	TMXLayer *startPos = map->getLayer("START");
	map->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	map->setScale(scaleSize.width, scaleSize.height);
    
    // Get layer name "START" position and set
	while (y<10)
	{
		while (x<5)
		{
            // No tile
			if (startPos->getTileAt(Vec2(x, 10-y-1)) == nullptr)
			{
			}
			else
			{
				map->setPosition(displaySize.width * 0.50f -((x*startPos->getTileSet()->_imageSize.width) + startPos->getTileSet()->_imageSize.width * 0.50f), 0);
				break;
			}
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;

    addChild(map);
    
    // Set tag map
	map->setTag(static_cast<int>(MoveDirection::Top));
    
	return true;
}


// Map move
void MapOperation::MoveMap(int tag)
{
	Vec2 pos, miniPos;
	
    // Get position now
	pos = getPosition();

	if (tag	== static_cast<int>(MoveDirection::Left))
	{
		setPositionX(pos.x += 2);
	}
	if (tag == static_cast<int>(MoveDirection::Right))
	{
		setPositionX(pos.x -= 2);
	}
	if (tag == static_cast<int>(MoveDirection::Top) || tag < 0)
	{
        setPositionY(pos.y -= 2);
	}
}


// Get layer name and "SAFE" or "OUT"
int MapOperation::GetLayerName(Point pt)
{
    // Position convert map position
    Point lp = map->convertToNodeSpace(pt);
    
    // SAFE
    TMXLayer *lay = map->getLayer("START");
    if (lay->getTileAt(Vec2(ceil(lp.x/700-1),ceil(10-lp.y/700-1))) != nullptr)
    {
        // Get mini map safe position
		prevPos = getPosition();
        return 1;
    }
    
    // SAFE
    lay = map->getLayer("ROAD");
    if (lay->getTileAt(Vec2(ceil(lp.x/700-1),ceil(10-lp.y/700-1))) != nullptr)
    {
		prevPos = getPosition();
        return 2;
    }
    
    // SAFE
    lay = map->getLayer("GOAL");
    if (lay->getTileAt(Vec2(ceil(lp.x/700-1),ceil(10-lp.y/700-1))) != nullptr)
    {
        return 3;
    }
    
    // OUT
    return 4;
}


// Map position restore
void MapOperation::RestorePos(int tag)
{
    if (tag	== static_cast<int>(MoveDirection::Left))
    {
        setPositionX(getPositionX() - map->getTileSize().width / 4);
    }
    if (tag == static_cast<int>(MoveDirection::Right))
    {
        setPositionX(getPositionX() + map->getTileSize().width / 4);
    }
    if (tag == static_cast<int>(MoveDirection::Top) || tag < 0)
    {
        setPositionY(getPositionY() + map->getTileSize().height / 4);
    }
    
    // Set tag map
	setTag(static_cast<int>(MoveDirection::Top));
}
