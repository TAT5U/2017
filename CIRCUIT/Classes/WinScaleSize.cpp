/*WinScaleSize.cpp*/

/*2017-07-29
	Tatsuya Kano
        Based Window Scale Size*/

// Include
#include "WinScaleSize.h"

// Constructor
WinScaleSize::WinScaleSize()
{

}


// Destructor
WinScaleSize::~WinScaleSize()
{

}

// Set calculation scale size
Size WinScaleSize::SetWinScaleSize()
{
    // Get display size
	Size displaySize = Director::getInstance()->getVisibleSize();

	// Get Window scale size
	GLView *gl = Director::getInstance()->getOpenGLView();
    
    // Return calculation size
	return Size(gl->getDesignResolutionSize().width / displaySize.width, gl->getDesignResolutionSize().height / displaySize.height);
}
